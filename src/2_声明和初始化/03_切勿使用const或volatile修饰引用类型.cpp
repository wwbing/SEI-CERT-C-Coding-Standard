#include <iostream>

void f(char c)
{
    // 这里const修饰char &类型的p变量，报错const' qualifier may not be applied to a reference
    char &const p = c;
    p = 'p';
    std::cout << c << std::endl;
}

void f1(char c)
{
    // 这里const修饰char类型的c以及c的引用别名p
    const char &p = c;
    p = 'p'; // Error: Cannot assign to variable 'p' with const-qualified type 'const char
}

void f2(char c)
{
    char &p = c;
    p = 'p';
}

int main()
{
    f('1');
}