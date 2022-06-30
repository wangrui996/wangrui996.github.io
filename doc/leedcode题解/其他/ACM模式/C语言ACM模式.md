# C语言ACM模式  


## scanf() & printf()   函数

* #include <stdio.h>

![image](https://user-images.githubusercontent.com/58176267/176389143-0a842ada-2419-4e55-9b98-f99a7ca71065.png)  

![image](https://user-images.githubusercontent.com/58176267/176395295-2c6f9153-2dcc-4af5-bf8e-073522f8b455.png)  

![image](https://user-images.githubusercontent.com/58176267/176430370-a8728eba-5336-4421-b88b-c5a7efec2399.png)  


* scanf("%u", sizeof(str)); %u表示无符号整型 sizeof返回的就是  


* printf输出格式总结：  
 
![image](https://user-images.githubusercontent.com/58176267/176455594-38cd3922-ebef-458f-b323-08b4e862f170.png)  


### 构造链表  

* 第一行给定了链表节点数量  
* 第二行为所有节点值 以空格隔开  

```c
5
6 7 8 9 10
```

```c
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

void printListNode(struct ListNode* head)
{   
    while(head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main(void) {

    int n;
    float c;
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* cur = head;
    scanf("%d", &n);

    for(int i = 0; i < n; ++i) {
        int temp;
        scanf("%d", &temp);
        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = temp;
        cur->next = node;
        cur = node;
    }
    cur->next = NULL;
    
    printListNode(head->next);

    return 0;
}
```

## getchar() & putchar() 函数

* #include <stdio.h>  

![image](https://user-images.githubusercontent.com/58176267/176389745-dd9dd84d-5eb2-4a81-adc8-fa11561068ee.png)


## gets() & puts() 函数  

* #include <stdio.h>

![image](https://user-images.githubusercontent.com/58176267/176390425-973a4768-56d7-403e-bad1-e04506d41a5f.png)


## getline() 函数  

https://blog.csdn.net/zxx910509/article/details/53196587  


## malloc函数  

![image](https://user-images.githubusercontent.com/58176267/176425215-52a887a6-db26-407a-9dad-f6fb218c84c4.png)  





