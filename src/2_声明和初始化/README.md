不要自己定义 C 风格的可变参数函数。

也就是不要写这种函数：
	int func(int a, ...)

这里的 ... 就是 C 风格可变参数


用 C++ 的模板参数包（parameter pack） 代替 C 风格
template <typename... Ts>