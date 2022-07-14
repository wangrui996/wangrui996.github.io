# STL   


## vector 和 list 的区别  

### vector
* vector和数组类似，拥有一段连续的内存空间，并且起始地址不变。
* 因此能高效的进行随机存取，时间复杂度为o(1);
* 但因为内存空间是连续的 (**因此支持[]运算符**)，所以在进行插入和删除操作时，会造成内存块的拷贝，时间复杂度为o(n)。
    * 在尾部插入，在不需要重新申请内存的时候用O(1)的时间，但是在头部插入速度慢
* 另外，当数组中内存空间不够时，会重新申请一块内存空间并进行内存拷贝。
    * 随机存取慢，但是插入和删除快，不需要拷贝和移动数据，只要通过改变指针的指向
### list  

* list是由双向链表实现的，因此内存空间是不连续的。
* 只能通过指针访问数据，所以list的随机存取非常没有效率，时间复杂度为o(n);
* 由于链表的特点，能高效地进行插入和删除。

## vector的erase  

* 删除容器某一个元素或某一区间元素

* [cplusplus函数原型](https://cplusplus.com/reference/vector/vector/erase/)  

* 如果不是删除末尾元素，需要移动删除区间后面的元素到新位置，线性复杂度 与list相比并不高效  

* 函数的返回值：一个迭代器，指向函数调用擦除的最后一个元素之后的元素的新位置。如果操作擦除了序列中的最后一个元素，返回的就是这是删除后的容器尾端end。 

* 注意迭代器的有效性：删除元素及其之后的迭代器都会失效(顺序容器中的list除外)，因此后面的元素都移动了，例如，之前定义了一个迭代器 iterator it = vec.end(); 在删除了一个中间元素后，没法再使用it了，它已经不指向末尾  
    * 对于顺序容器除了list，使用erase基本都有上面问题  
    * 对于关联容器，erase迭代器只是被删除的迭代器失效，返回值是void  


```cpp
// erasing from vector
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);

  // erase the first 3 elements:
  // 注意是前开后闭区间  
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}
```
* 运行：

```shell
myvector contains: 4 5 7 8 9 10
```

## swap 函数  

* 注意swap原型

```cpp
template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}
```

* 下面代码输出 2 1 3
```cpp
#include <vector>  
#include <iostream>
using namespace std;  
  
int main()  
{  
    vector<int> a = {1, 2, 3};
    swap(a[1], a[0]);
    
    for(int temp : a) {
        cout << temp << " ";
    }
    cout << endl;
    return 0;  
}  
```
[swap 函数原型-cplusplus](https://cplusplus.com/reference/utility/swap/?kw=swap)  

### swap函数实现vector动态释放内存  

* 由于vector内存只增不减，因此，比如一开始申请了大内存，后面通过pop_back或者erase删除了元素，改变的只是size，容量没有改变，还在继续占据内存  即使通过clear成员函数，也只是将size直接清为0，容量仍然不变；(**除了vector其他容器的clear一般会释放内存 比如顺序容器中的deque的成员函数clear，就会释放内存**) 因此，如果想要自己释放内存，可以借用vector的成员函数swap 

* **释放内存方法：利用匿名容器vector的成员函数swap，与要释放内存的容器交换，匿名对象在当前语句接收后会自动释放**   

```cpp
#include <vector>  
#include <iostream>

using namespace std;  
  
int main()  
{  
    vector<int> vec(1000, 0);
    
    cout << "vec capacity：" << vec.capacity()
         << "  vec size: " << vec.size() << endl;
    
    for(int i = 0; i < 900; ++i) {
        vec.pop_back();
    }
    
    cout << "vec capacity：" << vec.capacity()
         << "  vec size: " << vec.size() << endl;
         
    
    vector<int> temp(vec);
    cout << "temp capacity：" << temp.capacity()
         << "  temp size: " << temp.size() << endl;
    
    vector<int>(vec).swap(vec);
    
    cout << "vec capacity：" << vec.capacity()
         << "  vec size: " << vec.size() << endl;
    
    
    return 0;  
}  
```

* 输出  

```shell
vec capacity：1000  vec size: 1000
vec capacity：1000  vec size: 100
temp capacity：100  temp size: 100
vec capacity：100  vec size: 100
```

## map 

### 底层实现

* map和set属于标准关联容器，使用了非常高效的平衡二叉搜索树：红黑树  
* 插入和删除效率比其他序列容器高因为不需要左内存拷贝和移动，而是直接替换指向节点的指针  

### 优缺点



### 与其他容器的区别
* set和map区别在于，set只有key，map有一个key和它对应的value

* set和vector区别：set不包含重复元素， 


## set  

## unordered_map  

* 底层实现

* 优缺点

## unordered_set  


## map 和 unordered_map 的时间复杂度  

