#include "webserver.h"



WebServer::WebServer() 
{
    users = new http_conn[MAX_FD]; // 初始化 http保存客户端信息的数组

}


WebServer::~WebServer() 
{

}

/**
 * @brief 初始化服务器 
 * @param[in] port             端口号
 * @param[in] threadNum        线程池线程数 
 * @param[in] trigMode         触发模式  
 * @param[in] actorMode        事件处理机制
 */
void WebServer::init(int port, int threadNum, int trigMode, int actorMode) {

    m_trigMode = trigMode;
    m_actorMode = actorMode; // 0 : Proactor   1 : Reactor
}



void WebServer::setTrigMode() {
    // LT + LT
    if(0 == m_trigMode) {
        m_listenTrigMode = LT_MODE;
        m_connectTrigMode = LT_MODE;
    }
    // LT + ET 
    else if(1 == m_trigMode) {
        m_listenTrigMode = LT_MODE;
        m_connectTrigMode = ET_MODE;
    }
    // ET + LT
    else if(2 == m_trigMode) {
        m_listenTrigMode = ET_MODE;
        m_connectTrigMode = LT_MODE;
    }
    // ET + ET
    else if(3 == m_trigMode) {
        m_listenTrigMode = ET_MODE;
        m_connectTrigMode = ET_MODE;
    }
}


void WebServer::initThreadPool() 
{
    // 初始化线程池  
    try {
        m_threadpool = new threadpool<http_conn>(m_thread_num);
    } catch(...) {
        exit(-1);
    }
}


void WebServer::eventListen() 
{
    int ret;
    // 网络编程基础
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);

    // 优雅关闭连接  

    // 设置端口复用（绑定地质结构前设置）  
    int flag = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

    // 绑定地址结构  
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    ret = bind(m_listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret >= 0);
    ret = listen(m_listenfd, 5);
    assert(ret >= 0);

    
    // epoll相关  

    // 创建epoll对象
    m_epollfd = epoll_create(10);
    assert(m_epollfd >= 0);
    // epoll创建内核事件表
    // epoll_event events[MAX_EVENT_NUMBER]; 已经有一个成员了？
    
    // 添加监听文件描述符到 epoll对象中，后续还需要添加其它文件描述符，因此干脆封装到了Utils类中，在WebServer类中定义一个Utils成员  
    utils.addfd(m_epollfd, listenfd, false, m_listenTrigMode); // listenfd 不需要添加EPOLLONESHOT事件，因为它只会在主线程被操作
    http_conn::m_epollfd = m_epollfd;  // http_conn的静态成员初始化  



}

// 处理新的客户端连接
bool WebServer::dealListenEvents() {
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    if(LT_MODE == m_listenTrigMode) {
        int connfd = accept(m_listenfd, (struct sockaddr *)&client_address, &client_address_len);
        if(connfd < 0) {
            // TODO  日志  
            printf("accept error, errno is: %d\n", errno);
            return false;
        }
        if(http_conn::m_user_count >= MAX_FD) {
            // 当前连接数已达上限 
            // TODO  给客户端写信息  如服务器正忙     
            // 关闭connfd描述符等  
            close(connfd);
            return false;
        }
        // TODO  定时器
        // 初始化 客户端
        user[connfd].init(connfd, client_address, m_connTrigMode); // 这里直接将connfd作为客户端数组下标，后续查找起来比较方便
    } else {  // ET模式  
        while(1) {
            int connfd = accept(m_listenfd, (struct sockaddr *)&client_address, &client_address_len);      
            // ET模式下, listenfd上触发一次EPOLLIN事件，需要不断循环调用accpet以接收就绪队列中所有的连接
            // 直到调用accept失败或者建立连接的客户端数量超过上限  
            if(connfd < 0) {
                // TODO  日志  
                printf("accept error, errno is: %d\n", errno);
                break;
            }
            if(http_conn::m_user_count >= MAX_FD) {
                // 当前连接数已达上限 
                // TODO  给客户端写信息  如服务器正忙     
                // 关闭connfd描述符等  
                close(connfd);
                break;
            }
            user[connfd].init(connfd, client_address, m_connTrigMode);
        }
        return false;
    }
    return true;
}

// 处理读事件
void dealwithread(int sockfd) {

    // Reactor
    if(1 == m_actorMode) {

    }
    // 模拟Proactor
    else {
        if(user[sockfd].read_once()) { // 一次性把数据都读出来
            // TODO: 打印提示信息 info 

            // 成功读完数据，将该任务加入到请求队列
            m_threadpool->append(&user[sockfd]);
        }
        // 读失败
        else {
            user[sockfd].close_conn();
        }

    }
}



// 处理写事件
void dealwithwrite(int sockfd) {

    // Reactor
    if(1 == m_actorMode) {
    
    }
    // Proactor
    else {
        // 尝试一次性写完所有数据  
        if(user[sockfd].write()) { 
            // TODO: 打印信息   
            // 写成功，一般不需要其它处理  
        }
        else {
            user[sockfd].close_conn();
        }
    }
}


void WebServer::eventLoop() {

    while(true) {
        int number = epoll_wait(m_epollfd, m_events, MAX_EVENTS_NUMBER, -1);
        if(number < 0 && (errno != EINTR)) { // 返回但是没有事件发生，且不是由于信号打断，则认为调用失败
            // TODO  日志 
            printf("epoll_wait failed\n");
            break;
        }

        for(int i = 0; i < number; ++i) {
            int sockfd = m_events[i].data.fd;

            // 判断有事件的描述符是否为 listenfd  是的话处理新的客户端连接  
            if(sockfd == m_listenfd) {
                bool flag = dealListenEvents();
                if(false == flag) {
                    continue;
                }
            } 
            // 客户端异常断开，错误等
            else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) { // 与异常断开相关的事件
                // 对方异常断开、错误等事件发生  
                // 服务器端关闭连接

                // TODO 移除对应的定时器

                users[sockfd].close_conn(); // 关闭连接
            }
            // 处理客户连接接收的数据
            else if(event[i].events & EPOLLIN) {
                dealwithread(sockfd);
            }
            // 写事件
            else if(event[i].events & EPOLLOPOUT) {
                dealwithwrite(sockfd);
            }
        } 
    }

}