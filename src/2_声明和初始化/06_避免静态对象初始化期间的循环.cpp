#include <iostream>

/*
    静态对象的初始化时机很特殊，
    如果初始化过程中又反过来依赖自己，或者依赖一个还没准备好的静态对象，就会出问题。
*/

int fact(int i) noexcept(false)
{
    if (i < 0)
    {
        // 斐波那契数列无法小于0定义
        throw std::domain_error("i must be >= 0");
    }

    // 局部静态变量初始化，第一次进入fact的时候都会初始化这个cache，导致死循环
    // terminate called after throwing an instance of '__gnu_cxx::recursive_init_error'
    
    static const int cache[] = {fact(0), fact(1), fact(2), fact(3), fact(4), fact(5), fact(6), fact(7), fact(8), fact(9), fact(10), fact(11), fact(12), fact(13), fact(14), fact(15), fact(16)};

    if (i < (sizeof(cache) / sizeof(int)))
    {
        return cache[i];
    }
    
    return i > 0 ? i * fact(i - 1) : 1;
}

int main()
{
	fact(2);
    return 0;
}