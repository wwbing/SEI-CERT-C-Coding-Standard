#include <cstdarg>
#include <iostream>
#include <type_traits>


/*
	不要自己定义 C 风格的可变参数函数。

	也就是不要写这种函数：
		int func(int a, ...)	这里的 ... 就是 C 风格可变参数


	用 C++ 的模板参数包（parameter pack） 代替 C 风格
	template <typename... Ts>

*/

// 不合规代码：基础的C风格 可变参 add函数;  ... 的写法无类型检查
int CStyle_add(int first, int second, ...)
{
    int r = first + second;
    va_list va;
    va_start(va, second);

    while (int v = va_arg(va, int)) {
        r += v;
    }

    va_end(va);
    return r;
}

// 合规思路：模板实例化有参数类型检查

// 合规代码1：递归展开模板参数包
template <typename Arg, typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
int add(Arg f, Arg s)
{
    return f + s;
}
template <typename Arg, typename... Ts, typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
int add(Arg f, Ts... rest)
{
    return f + add(rest...);
}


// 合规方案 2：用初始化列表展开
template <typename Arg, typename... Ts, typename std::enable_if<std::is_integral<Arg>::value>::type * = nullptr>
int add_initial(Arg i, Arg j, Ts... all)
{
    int values[] = {j, all...};
    int r = i;
    for (auto v : values) {
        r += v;
    }
    return r;
}

int main()
{
    // 正常情况
    std::cout << CStyle_add(1, 2, 3, 4, 5, 0) << std::endl;

    // 异常情况：无类型检查 -> undefined behavior，当前的编译器double的3.14按照int读进去-> 0
    std::cout << CStyle_add(1, 2, 3.14, 1, 0) << std::endl;

    std::cout << add(1, 2, 3, 4, 5, 6) << std::endl;

    // std::cout << add(1, 2, 3.14, 4, 5, 6) << std::endl;
    // 编译不过，无法实例化函数出来

    std::cout << add_initial(1, 2, 3, 4, 5, 6, 7) << std::endl;
    // std::cout << add_initial(1, 2, 3, 4, 5, 6, 7.12) << std::endl;
    // 编译不过，无法实例化函数出来
    
    return 0;
}