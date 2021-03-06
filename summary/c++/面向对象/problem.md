# 1、⾯向对象的三⼤特征是哪些？各自有什么样的特点？
封装：将客观事物封装成抽象的类，⽽类可以把⾃己的数据和⽅法暴露给可信的类或者对象，对不可信的类或对象则进⾏信息隐藏。
继承：类之间相关的关系，使得一种对象可以继承拥有另外一类对象的特征和能力，并且⽆需重新编写原来的类,除此之外，还可对功能进行拓展。作用：避免公用代码的重复开发，减少代码冗余。
多态：一个接口，多种方法。

# 2.多态的实现有几种？
静态多态：
编译器在编译阶段时期就确定的，实现通过函数重载和函数模板实现的。
动态多态：
编译器在运行时期完成的，通过虚函数机制和继承关系实现的，通过基类指针或引用调用虚函数，执行动态绑定。

## 3.动态多态的作用？

## 5.动态绑定是如何实现的？
当基类指针或引用调用虚函数的时候，发生动态绑定。动态绑定是通过虚函数和继承机制实现的。当类中有虚函数的时候，编译器会为每个类创建一个虚函数表，把虚函数的入口地址放入虚函数表中，类的每个对象保存一个指向该类虚函数表的指针vptr。派生类会继承类的所有虚函数，当派生类覆盖基类的虚函数的时候，虚函数表中相应函数的地址将转换成派生类对应的函数地址。在运行时根据基类指针或引用指向的对象，调用该对象的虚函数表指针，到相应的虚函数表中寻找要执行的函数。

## 6.纯虚函数有什么作用？如何实现？
实现一个统一的接口，起到规范作用，规范继承这个类必须要实现该函数。
virtual void fun() = 0;

## 7.虚函数表是针对类的还是针对对象的？同⼀个类的两个对象的虚函数表是怎么维护的？
虚函数表是针对类的，类的所有对象共享该虚函数表，每个对象内部都保存一个指向该类虚函数表的指针vptr,每个对象的vptr存放地址不同，但都指向同一虚函数表。

## 9.为什么基类的析构函数需要定义为虚函数？
由于类的多态性，可以使用基类指针或引用指向派生类对象，在删除基类指针的时候，假如析构函数不是虚函数，此时采用的是静态绑定，所以只会调用基类的析构函数而不会调用派生类的析构函数，这样只能销毁派生类中的部分数据，无法正确销毁对象，导致内存泄漏。	

## 10.构造函数可以是虚函数吗？
不能。
+ 创建一个对象会指明他的类型，对象创建成功后编译器获取他的实际类型。但虚函数是在运行期间才能确定调用的是哪一类型的函数，对象没创建完成前虚构造函数无法知道动态类型，也就是调用的是继承树上的哪一类型，不调用虚构造函数又无法创建对象，这样就形成了死锁。 
+ 虚函数是通过指向虚函数表的指针来初始化的。而虚函数表指针是在构造函数的时候初始化的。构建一个对象的时候，是先申请内存再调用构造函数。如果构造函数是虚函数，我们需要通过虚函数指针来找到虚构造函数的入口，但此时内存中还没有完成初始化，所以没有虚函数指针，因此构造函数不能是虚函数。

## 11.如何让一个类不能实例化？
纯虚函数或者构造函数声明为private。

## 12.若类A是一个空类，那么sizeof(A)的值为多少，为什么？
sizeof(A)的值为1，类的每个实例在内存中都有一个独一无二的地址，为了达到这个目的，编译器往往会给一个空类隐含的加一个字节，这样空类在实例化后在内存得到了独一无二的地址。

## 13.构造函数和析构函数可以抛出异常吗？
从语法上讲，两者都可以抛出异常。
但从风险控制的角度来说，构造函数可以抛出异常，析构函数最好不要抛出异常。原因有2点
+ 析构函数抛出异常的点后的操作无法执行。假如存在内存释放等关键操作，可能会导致内存泄漏的问题。
+ 2）通常异常发生时，c++的机制会调用已经构造对象的析构函数来释放资源，此时若析构函数本身也抛出异常，则前一个异常尚未处理，又有新的异常，会造成程序崩溃的问题。 [在发生异常的情况下调用析构函数抛出异常，会导致程序崩溃]

**解决方案**
+ 1) 如果某个操作可能会抛出异常，class应提供一个普通函数（而非析构函数），来执行该操作。目的是给客户一个处理错误的机会。

+ 2) 如果析构函数中异常非抛不可，那就用try catch来将异常吞下，必须要把这种可能发生的异常完全封装在析构函数内部，决不能让它抛出函数之外。

## 14.多继承的问题，如何消除二义性？
两个问题
+ 相同基类之间和基类与派生类之间的同名成员，会导致同名二义性（三角问题）。
	+ 在派生类中命名同名成员可以覆盖基类的成员
	+ 使用作用域运算符指明访问的是哪个父类的成员
+ 若一个类继承自多个类，而多个父类又有同一个基类派生而来，在访问共同基类的成员时候，会出现路径二义性（菱形问题）。
	+ 前两个方法同上
	+ 使用虚继承，虚基类，使得不同路径派生下的基类对象在最终派生类下只存在一个拷贝。（虚派生只影响从指定了虚基类的派生类中进一步派生出来的类，它不会影响派生类本身。）
A->B, A->C, B->D, C->D;
em:
+ 如果 B 和 C 中都没有 x 的定义，那么 x 将被解析为 A 的成员，此时不存在二义性。
+ 如果 B 或 C 其中的一个类定义了 x，也不会有二义性，派生类的 x 比虚基类的 x 优先级更高。
+ 如果 B 和 C 中都定义了 x，那么直接访问 x 将产生二义性问题。

## 15.c++中class与struct的区别
+ 成员默认访问权限，struct默认是public的，class默认是private的
+ 继承权限问题，struct默认是public继承，class默认是private继承的。
+ class还可以用于定义模板参数，struct不可以。

## 16.