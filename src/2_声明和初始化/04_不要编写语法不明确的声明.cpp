#include <iostream>
#include <mutex>

/*
    如果某段语法既可能是声明，也可能是表达式/对象构造，那么编译器倾向于把它当成声明
*/


// =======================典型例子1===================
static std::mutex m;
static int shared_resource;

void increment_by_42()
{
    /*
        std::unique_lock<std::mutex>(m);
            歧义：本来打算是创建一个unique_lock对象，利用RAII在该对象析构的时候自动解锁
        实际上：
            std::unique_lock<std::mutex>(m) 等价于 std::unique_lock<std::mutex> m；这就是一个m变量的声明
            在变量声明过程中运行括号的冗余 -> 所以甚至不会解析为一个临时对象的创建
        编译器的原则，在可以是声明的情况下，优先处理为声明

        可以改为：
			std::unique_lock<std::mutex> lock(m);
    */

    std::unique_lock<std::mutex>(m);
    shared_resource += 42;
}

// =======================典型例子2===================
struct Widget {
    Widget() { std::cout << "Constructed\n"; }
};

void f()
{
    /*
        Widget w();
        这行代码可能是我们以为声明一个Widget对象w，调用构造函数；
        实际上是被解析为一个w函数，函数参数为空，返回值为Widget

        可以改为：
        Widget w; 或者 widget w{};花括号初始化
    */
    Widget w();
}



// =======================典型例子3===================
struct Widget1 {
    explicit Widget1(int i) { std::cout << "Widget1 constructed" << std::endl; }
};
struct Gadget1 {
    explicit Gadget1(Widget1 wid) { std::cout << "Gadget1 constructed" << std::endl; }
};

void f1()
{
    int i = 3;
    Gadget1 g(Widget1(i));
    std::cout << i << std::endl;
}
/*
    Gadget1 g(Widget1(i));
    	原本的意思：先用i构造Widget1对象，再用这个对象构造Gadget1对象；
    	实际上被解析为：函数g，参数是i构造的Widget1对象，返回值是Gadget1对象；

    可以改为：
		Gadget1 g{Widget1(i)};
*/
int main()
{
}