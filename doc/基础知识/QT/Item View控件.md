# QListWidget控件  

### 添加一行内容 可设置对齐方式  

```cpp
//QListWidget对象 每一行都是一个QListWidgetItem
QListWidgetItem * item = new QListWidgetItem("举头望明月");
ui->listWidget->addItem(item);

//设置水平居中
item->setTextAlignment(Qt::AlignHCenter);
```  
![image](https://user-images.githubusercontent.com/58176267/156514195-2b87dc01-67a6-4823-b11e-c1af54a1a236.png)


### 一次性加入多行  

```cpp
//一次性加多行 QStringList  (List<string> List容器放的是string)
// QStringList----QList<string>
QStringList list;
list << "举头望明月" << "低头思故乡";
ui->listWidget->addItems(list);
```

# QTreeWidget  树控件  
下面代码中，设置水平头使用了**匿名对象**的概念  

```cpp
    //树控件 treeWidget
    //设置水平头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍"); //匿名对象

    //树控件的每一行都叫QTreeWidgetItem
    QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem * minItem = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem * zhiItem = new QTreeWidgetItem(QStringList() << "智力");
    //加载顶层的节点(根节点)
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(minItem);
    ui->treeWidget->addTopLevelItem(zhiItem);

    //追加子节点 也是 QTreeWidgetItem
    QStringList hero1;
    hero1 << "www" << "1111111111";
    QTreeWidgetItem * l1 = new QTreeWidgetItem(hero1);
    //追加子节点
    liItem->addChild(l1);
    //其他同理
```

# QTableWidget  表格控件  

注意：使用[]操作越界就挂了，使用at函数，越界后抛出异常

```cpp
    //TableWidget 控件
    //设置列数
    ui->tableWidget->setColumnCount(3);
    //设置表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "性别" << "年龄"); //水平表头

    //设置行数
    ui->tableWidget->setRowCount(5);

    //表格内容 QTableWidgetItem
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("wang")); //setItem需要的第三个参数，是一个QTableWidgetItem的指针
    QStringList nameList;
    nameList << "zhangsan" << "lisi" << "wangwu" << "chenliu" << "liuxiu";

    QList<QString> sexList;
    sexList << "男" << "男" << "男" << "男" << "女";

    for(int i = 0; i < 5; ++i)
    {
        int col = 0;
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(sexList.at(i)));
        // int转QStringList  QString::number(18)
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(QString::number(18)));
    }
```

# Scroll Area  
滚动区域  

![image](https://user-images.githubusercontent.com/58176267/156524629-c69d8826-bbf3-4a82-8438-09405d182dc4.png)

# Tool Box  

# Tab Widget 分页窗口  

* 1.修改名称 在属性栏  
* 2.添加窗口  右边选中该对象，选择插入页  

![image](https://user-images.githubusercontent.com/58176267/156525883-a5cf2dea-867a-43dd-b903-e4ff3ef28cc2.png)

# Stacked Widget 栈控件  

可以实现不同对象的循环显示，但是下面的黑箭头只在开发时使用，便于切换，想要最后程序执行效果有切换效果，需要添加其他控件如按钮  

![image](https://user-images.githubusercontent.com/58176267/156526798-6c2da755-e8f3-4062-a263-673d8813bf42.png)  
![image](https://user-images.githubusercontent.com/58176267/156526827-0ac05035-c4c8-417f-83c6-05fbec6bfb94.png)  

如通过两个按钮，按其中一个显示一个东西，按另外一个显示一个东西  
```cpp
    //栈控件使用  
    //设置默认值  不会根据ui设计界面去改变  
    ui->stackedWidget->setCurrentIndex(1);
    
    connect(ui->pushButton_28, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0); //去stackedWidget属性查
    });
    connect(ui->pushButton_29, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1); //去stackedWidget属性查
    });
```

# Dock Widget 浮动窗口  


# Combo Box  下拉框  


```cpp
    //下拉框
    //添加内容
    ui->comboBox->addItem("位置控制");
    ui->comboBox->addItem("速度控制");
    ui->comboBox->addItem("加速度控制");
    //点击按钮 选中速度控制
    connect(ui->pushButton_30, &QPushButton::clicked, [=](){
        ui->comboBox->setCurrentIndex(1);
    });
```
# Font Combo Box 字体下拉框  

# Line Edit 单行输入框  

可以通过设置属性中 echoMode 设置显示的情况，如密码模式  

# Text Edit 多行文本  

# Plain Text Edit  

通过它和Text Edit图标可以看出，Text Edit可设置颜色，字体，下划线，加粗等  
Plain Text Edit是纯文本  

# Spin Box 数字加减  

# Double Spin Box 双精度数字的加减  

# Time Edit 时间  

# Date Edit 日期  

# Horizontal Scroll Bar 水平滚动条  

# Horizontal Slider 另一种形式的水平滚动条  

上面两类滚动条可以配合Spin Box使用，实现动一个控件另一个跟着动  
可以自定义封装成一个控件  

# Label  标签  

不仅可以显示文本，也可显示图片等  

```cpp
    //利用Lable显示图片
    ui->label->setPixmap(QPixmap(":/resurces/image/Axes.png"));

    //利用Lable显示gif图片
    QMovie * movie = new QMovie(":/resurces/image/t.gif");
    ui->label->setMovie(movie); //查看setMovie()需要QMovie对象的一个指针
    //播放动态图
    movie->start();
```
 





