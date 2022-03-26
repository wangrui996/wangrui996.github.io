


## demo 

```cpp
#include <iostream>
#include <thread> 

void print1()
{
    while(1)
    {
        std::cout << "hello" << "world" << std::endl;
    }
}


void print2()
{
    while(1)
    {
        std::cout << "wang" << "rui" << std::endl;
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
hellowangrui
wangrui
wangrui
wangrui
worldwangrui
wang
helloworld
helloworld
helloworld
helloworld
helloworld
helloworld
helloworld
helloworld
helloworld
helloworld
rui
hellowangrui
wangrui
wangworldrui
helloworld

```







