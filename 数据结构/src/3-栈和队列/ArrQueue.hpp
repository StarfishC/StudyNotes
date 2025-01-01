// File:    ArrQueue.hpp
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <iostream>
#include <cstddef>

template<typename T>
class ArrQueue
{
public:
    ArrQueue(size_t size);
    ~ArrQueue();

    void Clear(); // 清空队列
    bool IsEmpty(); // 判断队列是否为空
    bool IsFull(); // 判断队列是否已满
    bool EnQueue(const T& item); // 入队
    bool DeQueue(T& item); // 出队
    bool Front(T& item); // 返回队首元素
    size_t Length(); // 队列长度
private:
    size_t size_; // 存放队列的数组大小
    int front_; // 表示队首位置
    int rear_; // 表示队尾位置
    T* queue_; // 存放队列元素的数组
};

template<typename T>
ArrQueue<T>::ArrQueue(size_t size) :
    size_(size), front_(0), rear_(0), queue_(new T[size_])
{
}

template<typename T>
ArrQueue<T>::~ArrQueue()
{
    delete[] queue_;
}

template<typename T>
inline void ArrQueue<T>::Clear()
{
    front_ = rear_ = 0;
}

template<typename T>
inline bool ArrQueue<T>::IsEmpty()
{
    return front_ = rear_;
}

template<typename T>
inline bool ArrQueue<T>::IsFull()
{
    return (rear_ + 1) % size_ == front_;
}

template<typename T>
bool ArrQueue<T>::EnQueue(const T& item)
{
    if (IsFull())
    {
        std::cout << "队列满\n";
        return false;
    }
    queue_[rear_] = item;
    rear_ = (rear_ + 1) % size_;
    return true;
}

template<typename T>
bool ArrQueue<T>::DeQueue(T& item)
{
    if (IsEmpty())
    {
        std::cout << "队列空\n";
        return false;
    }
    item = queue_[front_];
    front_ = (front_ + 1) % size_;
    return true;
}

template<typename T>
bool ArrQueue<T>::Front(T& item)
{
    if (IsEmpty())
    {
        std::cout << "队列空，无元素\n";
        return false;
    }
    item = queue_[front_];
    return true;
}

template<typename T>
size_t ArrQueue<T>::Length()
{
    size_t len;
    if (IsEmpty())
        len = 0;
    else if (front_ <= rear_)
        len = rear_ - front_;
    else
        len = size_ + rear_ - front_;
    return len;
}
