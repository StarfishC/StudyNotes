// File:    LinkStack.hpp
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <cstddef>
#include <iostream>
#include "../2-线性表/LinkList.hpp" // 引入Link节点

template<typename T>
class LinkStack
{
private:
    Link<T>* top_; // 指向栈顶指针
    size_t size_; // 存放栈顶元素的个数
public:
    LinkStack();
    ~LinkStack();

    void Clear(); // 清空栈
    void Push(const T& item); // 入栈
    bool Pop(T& item); // 出栈
    bool Top(T& item); // 返回栈顶内容
    bool IsEmpty(); // 判断栈空
};

template<typename T>
LinkStack<T>::LinkStack() :
    top_(new Link<T>()), size_(0)
{
}

template<typename T>
LinkStack<T>::~LinkStack()
{
    Clear();
    delete top_;
}

template<typename T>
void LinkStack<T>::Clear()
{
    Link<T>* tmp = top_->next;
    while (tmp)
    {
        Link<T>* t = tmp;
        tmp = tmp->next;
        delete t;
    }
    top_->next = nullptr;
    size_ = 0;
}

template<typename T>
void LinkStack<T>::Push(const T& item)
{
    Link<T>* tmp = new Link<T>(item, top_->next);
    top_->next = tmp;
    size_++;
}

template<typename T>
bool LinkStack<T>::Pop(T& item)
{
    if (IsEmpty())
    {
        std::cout << "栈空!\n";
        return false;
    }
    Link<T>* tmp = top_->next;
    top_->next = tmp->next;
    item = tmp->data;
    delete tmp;
    size_--;
    return true;
}

template<typename T>
bool LinkStack<T>::Top(T& item)
{
    if (IsEmpty())
    {
        std::cout << "栈空!\n";
        return false;
    }
    item = top_->next->data;
    return true;
}
