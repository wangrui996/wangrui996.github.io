


## demo 

```cpp
#include <iostream>
#include <thread> 

void print1()
{
    while(1)
    {
        std::cout << "hello word" << 1 << std::endl;
    }
}


void print2()
{
    while(1)
    {
       std::cout << "wang rui" << 2 << std::endl;
    }

}


int main(int argc, char** argv)
{

	std::thread th1(print1);
	std::thread th2(print2);
		
	th1.join();
	th2.join();
	
	return 0;
}
```

```shell
wang rui2
wang rui2hello word1
hello word1

wang rui2
wang rui2hello word1
hello word1

wang rui2
wang ruihello word1
hello word1
hello word1
hello word1
hello word1
2
wang rui2
wang rui2
wang rui2
wang rui2
wang rui2
wang ruihello word2
wang rui2
1wang rui2
wang rui2

hello word1
hello word1
hello word1
hello word1
hello word1
hello word1
```


## printf   



```cpp
#include <iostream>
#include <thread> 
#include <stdio.h>

void print1()
{
    while(1)
    {
        printf("hello world%d\n", 1);
    }
}


void print2()
{
    while(1)
    {
        printf("wangrui rui%d\n", 2);
    }

}


int main(int argc, char** argv)
{

	std::thread th1(print1);
	std::thread th2(print2);
		
	th1.join();
	th2.join();
	
	return 0;
}

```


```shell
hello world1
hello world1
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2
hello world1
hello world1
hello world1
hello world1
hello world1
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2
wangrui rui2

```




