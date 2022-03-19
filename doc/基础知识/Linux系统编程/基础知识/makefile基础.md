# makefile基础  


## 1 个规则  
目标：依赖条件
（一个 tab 缩进）命令

* 1. 目标的时间必须晚于依赖条件的时间，否则，更新目标  

* 2. 依赖条件如果不存在，找寻新的规则去产生依赖条件  

* makefile默认遇到的第一个目标最终目标     可以使用 “ALL：目标”  指定 makefile 的终极目标  

## 2 个函数  
makefile中只有一种类型就是字符串，一次你不需要声明直接用

### src = $(wildcard ./*.c)   匹配当前工作目录下的所有.c 文件。将文件名组成列表，赋值给src     

* 如当前工作目录下右add.c, sub.c和div1.c，Makefile中src = $(wildcard *.c)得到的src = add.c sub.c div1.c 


### obj = $(patsubst %.c, %.o, $(src))     将参数 3 中，包含参数 1 的部分，替换为参数 2  

* $(src)意思是对src取值  上面例子中   如前面写了src = $(wildcard ./*.c)，则取出的值为 add.c sub.c div1.c， 

* 现在obj = $(patsubst %.c, %.o, $(src))   意思是，将add.c sub.c div1.c中的.c替换为.o  
* obj = add.o sub.o div1.o
* 如果是obj = $(patsubst %.c, %, $(src)) 得到的 obj = add sub div1  


#### 利用两个函数写的Makefile  

```shell
src = $(wildcard, ./*.c) 或者 src = $(wildcard, *.c)  # src = add.c sub.c div.c hello.c  

obj = $(patsubst %.c, %.o, $(src))    # obj = add.o sub.o div1.o hello.o  

a.out: $(obj)  
    gcc $(obj) -o a.out  

add.o:add.c
    gcc -c add.c -o add.o
sub.o:sub.c
    gcc -c sub.c -o sub.o
div1.o:div1.c
    gcc -c div1.c -o div1.o
hello.o:hello.c
    gcc -c hello.c -o hello.o

clean：
    -rm -rf $(obj) a.out
```


## clean:   命令 (没有依赖)

-rm -rf $(obj) a.out        “-”： rm前面的横杠作用是，删除不存在文件时，不报错  顺序执行结束   如我们已经不小心删除了一个hello.o，再用make clean 找不到hello.o的时候不会报错 

Makefile中有了clean后，make clean可只执行clean目标  

* **可以先执行make clean -n 查看make clean会执行什么，比如clean中写错了-rm -rf $(src) a.out**


## 3 个自动变量  

注意三个自动变量只能出现在一组规则的命令位置，目标的位置不能出现 

* $@: 在规则的命令中，表示规则中的目标 

* $^: 在规则的命令中，表示所有依赖条件  

* $<: 在规则的命令中，表示第一个依赖条件  **如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则**
    *  

```shell
src = $(wildcard, ./*.c) 或者 src = $(wildcard, *.c)  # src = add.c sub.c div.c hello.c  

obj = $(patsubst %.c, %.o, $(src))    # obj = add.o sub.o div1.o hello.o  

a.out: $(obj)  
    gcc $^ -o $@    # $(obj)是这个规则的依赖(也就是add.o sub.o div1.o hello.o)  所以这里$^可以代替这个规则的所有依赖   $@表示该组规则中的目标也就是a.out

add.o:add.c
    gcc -c $< -o $@   # 这里只有一个规则用$^也可
sub.o:sub.c
    gcc -c $< -o $@
div1.o:div1.c
    gcc -c $< -o $@
hello.o:hello.c
    gcc -c $< -o $@

clean：
    -rm -rf $(obj) a.out
```

## 模式规则  

%.o:%.c
 gcc -c $< -o %@

* $< 还有个作用是**如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则**    如下面例子中有个模式规则，它会将依赖列表也就是$(obj)中的依赖依次取出套用模式规则 
* 这样，就能实现一条模式规则完成了多个源文件编译的工作

```shell
src = $(wildcard, ./*.c) 或者 src = $(wildcard, *.c)  # src = add.c sub.c div.c hello.c  

obj = $(patsubst %.c, %.o, $(src))    # obj = add.o sub.o div1.o hello.o  

a.out: $(obj)  
    gcc $^ -o $@    # $(obj)是这个规则的依赖(也就是add.o sub.o div1.o hello.o)  所以这里$^可以代替这个规则的所有依赖   $@表示该组规则中的目标也就是a.out

%.o:%.c
 gcc -c $< -o %@

clean：
    -rm -rf $(obj) a.out
```

**好处** ：方便扩展


### 静态模式规则  
指定漠视规则给谁用  
$(obj):%.o:%.c
 gcc -c $< -o %@

意思是，$(obj)所使用的模式规则是  
%.o:%.c
    gcc -c $< -o %@

## 伪目标  

.PHONY: clean ALL

不管clean条件满足与否都要执行  

如果不加，如果Makefile目录下有一个clean文件或者ALL文件，由于原来的clean:规则中，clean是没有依赖的，不需要判断时间，当有一个clean文件时，执行make clean会认为clean已经生成，规则中的命令就不会被执行  


## 参数  

* 如定义一个参数  myArgs= -Wall -g  希望编译时检查语法错误输出错误信息，-g希望编译的程序可以直接被调试  
    * 然后在每个规则的命令中，后面加上 $(myArgs)   如gcc -c $< -o %@ $(myArgs)

* -n：模拟执行 make、make clean 命令。
* -f：指定文件执行 make 命令  xxx.mk


## 总结  

可以将上述的源文件放在src目录下，将头文件放在include目录下，将生成的中间.o文件放在obj目录下，此时重新编写Makefile文件   


需要注意： 

* 此时 src = $(wildcard, ./src/*.c)  # src = ./src/add.c ./src/sub.c  .......

* obj = $(patsubst %.c, %.o, $(src))     将参数 3 中，包含参数 1 的部分，替换为参数 2  这个函数时，注意%通配符的含义，如果像这么写，意味着从$(src)这个值中，%表示.c前面的字符，然后 %.o中的%也表示.c前面的字符，两者是对应的，这么写的话 最后 obj = ./src/add.o ./src/sub.o  而我们希望的是后面静态模式规则中源文件生成的.o文件放在obj下，所以这里应该写成  
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))   # obj = ./obj/add.o ./obj/sub.o  

* 静态模式规则也要修改  


```shell
src = src = $(wildcard, ./src/*.c)  # src = src = ./src/add.c ./src/sub.c  .......

obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))    # obj = ./obj/add.o ./obj/sub.o  

a.out: $(obj)  
    gcc $^ -o $@    

$(obj):./obj/%.o:./src/%.c          # 对于$(obj)中的值(目标)，都用后面的模式规则生成  即依赖src下源文件在obj目录下生成同名的.o文件  需要的命令是gcc -c $< -o %@
    gcc -c $< -o %@                 # 相当于会执行 gcc -c ./src/add.c -o ./obj/add.o  ...........

clean：
    -rm -rf $(obj) a.out
```
