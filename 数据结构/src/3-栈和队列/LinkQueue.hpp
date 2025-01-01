// File:    LinkQueue.hpp
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <cstddef>
#include <iostream>
#include "../2-线性表/LinkList.hpp"

template<typename T>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue();

    void Clear(); // 清空队列元素
    bool EnQueue(const T& item); // 入队
    bool DeQueue(T& item); // 出队
    bool Front(T& item); // 返回队首元素
    bool IsEmpty(); // 队列是否为空
    size_t Length(); // 队列长度
private:
    size_t size_; // 队列元素个数
    Link<T>* front_; // 队首指针
    Link<T>* rear_; // 队尾指针
};

template<typename T>
LinkQueue<T>::LinkQueue() :
    size_(0), front_(nullptr), rear_(nullptr)
{
}

template<typename T>
void LinkQueue<T>::Clear()
{
    while (front_ != nullptr)
    {
        rear_ = front_;
        front_ = front_->next;
        delete rear_;
    }
    front_ = rear_ = nullptr;
    size_ = 0;
}

template<typename T>
bool LinkQueue<T>::EnQueue(const T& item)
{
    if (IsEmpty())
        front_ = rear_ = new Link<T>(item, nullptr);
    else
    {
        rear_->Next = new Link<T>(item);
        rear_ = rear_->Next;
    }
    size_++;
    return true;
}

template<typename T>
bool LinkQueue<T>::DeQueue(T& item)
{
    if (IsEmpty())
    {
        std::cout << "队列空，不能出队\n";
        return false;
    }
    item = front_->Data;
    Link<T>* tmp = front_;
    front_ = front_->Next;
    delete tmp;
    if (front_ == nullptr)
        rear_ = nullptr;
    size_--;
    return true;
}

template<typename T>
bool LinkQueue<T>::Front(T& item)
{
    if (IsEmpty())
    {
        std::cout << "队列空，不能出队\n";
        return false;
    }
    item = front_->Data;
    return true;
}

template<typename T>
inline bool LinkQueue<T>::IsEmpty()
{
    return size_ == 0;
}

template<typename T>
size_t LinkQueue<T>::Length()
{
    // return Size;
    size_t len = 0;
    for (Link<T>* tmp = front_; front_ != rear_; tmp = tmp->Next)
        len++;
    return len;
}
