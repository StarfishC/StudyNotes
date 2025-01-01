// File:    ArrStack.hpp
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <cstddef>
#include <iostream>

template<typename T>
class ArrStack
{
public:
    ArrStack(size_t size);
    ~ArrStack();

    void Clear(); // 清空栈元素
    void Push(const T& item); // 入栈
    bool Pop(T& item); // 出栈
    bool Top(T& item); // 返回栈顶元素
    bool IsEmpty(); // 判断栈控
    bool IsFull(); // 判断栈满
private:
    size_t size_; // 栈的大小
    int top_; // 栈顶位置
    T* st_; // 栈数组
};

template<typename T>
ArrStack<T>::ArrStack(size_t size) :
    size_(size), top_(-1), st_(new T[size])
{
}

template<typename T>
ArrStack<T>::~ArrStack()
{
    delete[] st_;
}

template<typename T>
inline void ArrStack<T>::Clear()
{
    top_ = -1;
}

template<typename T>
void ArrStack<T>::Push(const T& item)
{
    if (IsFull())
        std::cout << "栈满!\n";
    else
        st_[++top_] = item;
}

template<typename T>
bool ArrStack<T>::Pop(T& item)
{
    if (IsEmpty())
    {
        std::cout << "栈空!\n";
        return false;
    }
    item = st_[top_--];
    return true;
}

template<typename T>
bool ArrStack<T>::Top(T& item)
{
    if (IsEmpty())
    {
        std::cout << "栈空!\n";
        return false;
    }
    item = st_[top_];
    return true;
}

template<typename T>
inline bool ArrStack<T>::IsEmpty()
{
    return top_ == -1;
}

template<typename T>
inline bool ArrStack<T>::IsFull()
{
    return top_ == size_ - 1;
}
