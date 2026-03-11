#include <cstddef>
#include <iostream>
#include <new>

// 内存日志记录
void update_bookkeeping(void *allocated_ptr, std::size_t size, bool alloc)
{
    if (alloc) {
        std::cout << "[bookkeeping] 记录分配: " << allocated_ptr
                  << ", 大小: " << size << " 字节\n";
    } else {
        std::cout << "[bookkeeping] 记录释放: " << allocated_ptr
                  << ", 大小: " << size << " 字节\n";
    }
}

class Data
{
  private:
    int a, b, c;

  public:
    void *operator new(std::size_t size) noexcept(false)
    {
        void *ptr = ::operator new(size);
        update_bookkeeping(ptr, size, true);
        return ptr;
    }
    //void operator delete(void *ptr) noexcept
    //{
    //    update_bookkeeping(ptr, sizeof(Data), false);
    //    ::operator delete(ptr);
    //}
};

int main()
{
    // Data *data = static_cast<Data*>(Data::operator new(sizeof(Data)));
    Data *data = new Data;
    delete data;

    /*
        只有一个申请的日志，没有释放的日志，因为Data没有实现delete运算符。
        这里delete data不崩的原因是：Data::operator new内部也是调用的默认的全局::operator new

        改进：
            Data 作用域加上对应的delete 运算符的重写

            void operator delete(void *ptr) noexcept
            {
                update_bookkeeping(ptr, sizeof(Data), false);
                ::operator delete(ptr);
            }
    */
    return 0;
}