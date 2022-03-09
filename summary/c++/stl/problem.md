## 1.什么是STL？
标准模板库。六大组件
+ 容器：容纳、包含一组元素或元素集合的对象，序列容器和关联容器。
+ 算法：用于处理群集元素的算法。
+ 迭代器：不暴露容器内部结构的情况下对容器的遍历。
+ 适配器：转换器。把一种接口转换成另一种接口
  + 容器适配器：stack,queue是底层基于deque的适配器。
  + 迭代器适配器: 插入、反向、IO流。
  + 函数适配器：仿函数、成员函数、普通函数
+ 函数对象：仿函数，行为类似函数的对象，重载了operator()。
+ 配置器（两极配置器： ）: 负责空间配置与管理。

## 2.什么时候需要用unordered_map， 什么时候需要用map?


## 4.vector的底层原理及其相关面试题？
（1）vector底层原理
vector底层是一个动态连续的数组，三个迭代器，start, finish, end_of_storage。
start指向容器起始字节, finish指向最后一个元素的末尾字节，end_of_storage指向vector容器所占用内存空间的末尾字节。
空间不足以装下数据的时候。
+ 申请新的内存空间（1.5倍～2倍）
+ 将旧内存空间的数据拷贝到新的内存空间。
+ 释放旧的内存空间。
clear只删除数据，不释放存储空间。
对vector的任何操作引起了空间的重新配置，指向原vector的所有迭代器都会失效。

（2）vector是resize和reserve的区别？
reserve扩容，<才有变动，可以减少多次开辟、释放空间的问题（push_back())，提高效率。resize改变内部元素大小，capacity的大小也会改变。

（3）vector中size和capacity的区别？
size指当前vector有多少个元素(finish - start)。capacity指它已经分配的内存中可以容纳多少元素(end_of_storage - start)。

(4) vector的元素类型可以是引用吗？
vector的底层实现要求连续的对象排列，引⽤并⾮对象，没有实际地址，因此vector的元素类型不能是引⽤。

(5) vector迭代器失效问题
+ 内存重新分配的时候，原来所有迭代器都会失效。
+ insert(it, a)；在it的前方插入元素，erase(it, a)，删除it，返回指向下一个的迭代器。
+ 在向容器添加元素后，如果储存空间未重新分配，指向插入位置之前的元素的迭代器、指针、引用有效，但指向插入位置之后的将会失效。
在从容器删除元素之后，指向被删元素之前元素的迭代器、引用、指针仍有效。尾后迭代器也就失效。

(6) 释放vector内存
```cpp
vector().swap(vec);//清空内容且释放内存
vec.shrink_to_fit(); //请求容器降低capacity与size匹配。 由编译器决定要不要执行
vec.clear(); vec.shrink_to_fit(); //
```

(7) vector扩容为什么以1.5倍或者2倍扩容？
(8) vector常用
```cpp
vector<int> vec(10,100);
创建10个元素,每个元素值为100
vec.resize(r,vector<int>(c,0)); //二维数组初始化
reverse(vec.begin(),vec.end()) //将元素翻转
sort(vec.begin(),vec.end()); //排序，默认升序排列列
vec.push_back(val); //尾部插入数字
vec.size(); //向量⼤小
find(vec.begin(),vec.end(),1); //查找元素
iterator = vec.erase(iterator) //删除元素,返回后一个
it = vec.insert(it, a)；//it前面插入一个
```

## 5.list底层原理及其相关面试题
（1）
list底层是带头双向循环链表，链表每个节点为单位，存放当前值，next和pre指针。节点的地址在内存中不一定连续，每次插入删除元素，就配置或释放一个元素空间。
不适合随机访问，适合大量插入删除。
**（2）list的常用函数**
```cpp
list.push_back(elem)
list.pop_back()
在尾部加⼊入⼀一个数据
删除尾部数据
list.push_front(elem) 在头部插⼊入⼀一个数据
list.pop_front()
删除头部数据
上面四个都可以用emplace_XX代替
emplace(it, val)，在it前面插入val

list.size() 返回容器器中实际数据的个数
list.sort() 排序，默认由⼩小到⼤大
list.unique() 移除数值相同的连续元素
list.remove(5) 删除所有为5的
list.remove_if(可调用对象) 删除指定的
list.back() 取尾部迭代器器
list.erase(iterator) 删除⼀一个元素，参数是迭代器器，返回的是删除迭代器器的下⼀一个位置
list.splice(iter1, b, iter1, iter2); //把b链表中[iter1, iter2)的所有元素插入到a链表iter1前。
``` 

## 6.deque底层原理及其相关面试题
**(1)deque的底层原理**
元素分块存储，每个块都是连续的内存空间，有map块，每个map块存储指向每个存储块的首地址。
对于每个迭代器来说

[![bt3NJP.md.png](https://s4.ax1x.com/2022/03/03/bt3NJP.md.png)](https://imgtu.com/i/bt3NJP)

**迭代器内部结构**
```cpp
template<class T,...>
struct __deque_iterator{
    ...
    T* cur;
    T* first;
    T* last;
    map_pointer node;//map_pointer 等价于 T**
}
```
**deque实现**
```cpp
//_Alloc为内存分配器
template<class _Ty,
    class _Alloc = allocator<_Ty>>
class deque{
    ...
protected:
    iterator start;
    iterator finish;
    map_pointer map;

}
```
**维护start和finish迭代器，如下图**

cur当前正在遍历的元素，first指向当前连续空间的首地址。last当前连续空间的末尾地址。node是二级指针，指向指向当前空间的map数组的指针。每次deque在头部和尾部申请新空间，相当于map的头部和尾部申请新空间。


**（2）vector、list、deque使用场景**
vector可以随机存储元素（即可以通过公式直接计算出元素地址，⽽不需要挨个查找），但在⾮尾部插入删除数据
时，效率很低，适合对象简单，对象数量变化不大，随机访问频繁。除非必要，我们尽可能选择使用vector而非
deque，因为deque的迭代器⽐比vector迭代器复杂很多。
list不支持随机存储，适⽤于对象⼤大，对象数量变化频繁，插⼊和删除频繁，⽐如写多读少的场景。
需要从首尾两端进⾏插入或删除操作的时候需要选择deque。

```cpp
deque.push_back(elem) 在尾部加⼊入⼀一个数据。
deque.pop_back()
删除尾部数据。
在头部插⼊入⼀一个数据。
deque.push_front(elem)
deque.pop_front() 删除头部数据。
//emplace代替
deque.size() 返回容器器中实际数据的个数。
deque.at(idx) 传回索引idx所指的数据，如果idx越界，抛出out_of_range
```

## 7.map, multimap, set, multiset底层原理及相关面试题
（1）map, multimap, set, multiset底层原理。
map 、set、multiset、multimap的底层实现都是红⿊树，epoll模型的底层数据结构也是红⿊树，linux系统中CFS进程调度算法，也⽤到红⿊树。增删查改最坏情况下都是O(logn)

红黑树五个特点：
+ 每个节点要么红要么黑
+ 根必须是黑色
+ 叶子节点必须是黑的
+ 若一个节点是红色，两个儿子必须是黑的
+ 每个节点到其子孙节点上的所有路径上黑色节点数相同

stl map可以用count(返回0, 1)或者find() != mp.end()。

**（2）map 、set、multiset、multimap的特点**
+ set和multiset会根据特定的排序准则⾃动将元素排序，set中元素不允许重复，multiset可以重复。
map和multimap将key和value组成的pair作为元素，根据key的排序准则⾃动将元素排序（因为红黑树也是二叉搜索树，所以map默认是按key排序的），map中元素的key不允许重复，multimap可以重复。
map和set的增删改查速度为都是logn，是⽐较⾼效的。
 
**（3）为何map和set的插入删除效率⽐其他序列容器高，⽽且每次insert之后，以前保存的iterator不会失效？**

因为存储的是结点，不需要内存拷⻉和内存移动。
因为插⼊操作只是结点指针换来换去，结点内存没有改变。⽽iterator就像指向结点的指针，内存没变，指向内存
的指针也不不会变。

**（4）为何map和set不不能像vector⼀一样有个reserve函数来预分配数据?**

因为在map和set内部存储的已经不是元素本身了，⽽是包含元素的结点。也就是说map内部使⽤的Alloc并不是
map<Key, Data, Compare, Alloc>声明的时候从参数中传⼊的Alloc。

**（5）map 、set、multiset、multimap的常用函数**
```cpp
it map.begin() 返回指向容器器起始位置的迭代器器（iterator）
it map.end() 返回指向容器器末尾位置的迭代器器
bool map.empty() 若容器器为空，则返回true，否则false
it map.find(k) 寻找键值为k的元素，并⽤用返回其地址
int map.size() 返回map中已存在元素的数量量
map.insert({int,string}) 插⼊入元素
for (itor = map.begin(); itor != map.end();)
{
if (itor->second == "target")
map.erase(itor++) ; // erase之后，令当前迭代器器指向其后继。不会迭代器失效可以这么做
else
++itor;
}
```

## 8.unordered_map, unordered_set底层原理
**(1)unordered_map、unordered_set的底层原理**
unordered_map底层是一个哈希表（哈希函数使用取余法哈希函数）。数据的存储和查询的均摊复杂度O(1)， 但是消耗较多内存。
把key传入哈希函数后得到哈希值，使得key与一个哈希值唯一对应，不同的哈希值分类，相当于通过key进行分类，然后把元素存储在相应类所在的地方，称为桶。当hash值相同的时候，出现哈希冲突，unordered_map使用拉链法解决冲突。

拉链法：每个桶维护一个链表，冲突的元素插入到链表里面。

**(3)map与unordered_map的区别？使用场景**
+ 底层实现
map内部是红黑树实现的，该结构自动排序，所以map内都元素都是有序的，红黑树的每个节点相当于map的一个元素，所以对map的一系列操作相当于是对一颗红黑树操作，map的效率取决于红黑树，需要key相关的比较函数（<)。而unordered_map内部是一个采用拉链法实现的哈希表，元素是无序列的。所以需要哈希函数和==函数。
+ unordered_map的增删查改均摊下来是O(1)的，但是最坏时间复杂度可能达到O(n), 而map的各项操作的复杂度是稳定的O(logn), 但是哈希表的建立非常耗费时间，同时哈希表的内存消耗是很大的，特别在元素个数很多的时候哈希表的构建速度会很慢。
+ map内部是有序的，假如遇到与有序性相关的问题，可以考虑用map。遇到与查找元素相关的问题，unordered_map效率很高。

**（4）unordered_map、unordered_set的常⽤用函数**
```cpp
unordered_map.begin() 返回指向容器器起始位置的迭代器器（iterator）
unordered_map.end() 返回指向容器器末尾位置的迭代器器
unordered_map.cbegin() 返回指向容器器起始位置的常迭代器器（const_iterator）
unordered_map.cend() 返回指向容器器末尾位置的常迭代器器
unordered_map.size() 返回有效元素个数
unordered_map.insert(key) 插⼊入元素
unordered_map.find(key) 查找元素，返回迭代器器
unordered_map.count(key) 返回匹配给定主键的元素的个数
```

## 10.vector释放空间？
vector().swap(vec)

## 12.map插入方式有哪几种。
插入 {make_pair()},{} 

## 13.为什么vector的插入操作可能会导致迭代器失效?
vector动态增加大小的时候，并不一定在原空间后增加新的空间，可能以原大小的两倍在另外配置一片较大的新空间，然后拷贝，释放原来的内存，空间不一样，迭代器失效。

## 16.容器内部删除一个元素
1.序列式容器，vector, deque
erase迭代器不仅使所指向被删除的迭代器失效，⽽且使被删元素之后的所有迭代器失效(list除外)，所以不能使⽤。
需要it = c.erase(it);

2.关联容器(map, set, multiset, multimap)
erase迭代器只是被删除元素的迭代器失效，但是返回值是void，所以要采用erase(it++)的⽅式删除迭代器；
需要c.erase(it++)

## 17.vector越界访问下标，map越界访问下标？vector删除元素时会不会释放空间？
1. vector下标越界有部分编译器会检查，有些不会查。保证使用的时候下标不越界
2. map的下标访问相当于用查找key为下标的元素，若找到，返回value, 否则就会插入一个key = 下标，值默认初始化（一般为0）的元素。
3. vector erase的时候不会释放空间, 只是删除元素并返回迭代器的下一个迭代器.
deque可以在删除内容的同时释放内存.

## 18.map中[]与find的区别？
+ map的下标访问相当于用查找key为下标的元素，若找到，返回value, 否则就会插入一个key = 下标，值默认初始化（一般为0）的元素。
+ map的find函数：用key寻找，找到了返回该位置的迭代器，不存在这个关键码，返回尾迭代器。

## 20.频繁对vector push_back对性能影响的原因？
push_back的过程中，容器内部的size不断增加，一旦容器的size > capacity的时候，整个对象存储空间将重新分配，并拷贝原内存空间的元素到新内存空间中，这样性能开销大。