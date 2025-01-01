// File:    LinkList.hpp
// Author:  csh
// Date:    2021/02/20
// Update:  2024/12/10
// ===================

#include <cstdlib>
#include <iostream>

template<typename T>
class Link
{
public:
    Link(const T info, Link<T>* next_link = nullptr) :
        data(info), next(next_link) {}
    Link(Link<T>* next_link = nullptr) :
        next(next_link) {}

public:
    T data; // 数字域
    Link<T>* next; // 指针域
};

// 单链表
template<typename T>
class LinkList
{
public:
    LinkList();
    ~LinkList();

    bool Empty(); // 判断链表是否为空
    void Clear(); // 清空链表内容
    size_t length(); // 返回链表当前长度
    bool Append(const T& value); // 表尾添加新元素
    bool Insert(const int p, const T& value); // 位置p插入新元素value
    bool Remove(const int p); // 移除位置p元素
    bool GetValue(const int p, T& value); // 返回位置p的元素给value
    bool GetPos(int& p, const T value); // 返回值为value的位置
    void ShowAll(); // 显示链表的所有元素

private:
    Link<T>* SetPos(const int p); // 返回链表指向第p个元素的指针
    void Reset();

private:
    Link<T>* head_; // 单链表头节点
    Link<T>* tail_; // 单链表尾节点
};

template<typename T>
LinkList<T>::LinkList() :
    head_(new Link<T>()), tail_(head_)
{
}

template<typename T>
LinkList<T>::~LinkList()
{
    Reset();
}

template<typename T>
Link<T>* LinkList<T>::SetPos(const int p)
{
    int count = 0;
    if (p == -1)
        return head_;
    Link<T>* tmp = head_->next;
    while (tmp != nullptr && count < p)
    {
        tmp = tmp->next;
        count++;
    }
    return tmp;
}

template<typename T>
void LinkList<T>::Reset()
{
    Link<T>* tmp;
    while (head_ != tail_)
    {
        tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

template<typename T>
inline bool LinkList<T>::Empty()
{
    return head_ == tail_;
}

template<typename T>
void LinkList<T>::Clear()
{
    Reset();
    head_ = tail_ = new Link<T>();
}

// 求长度可以增加一个记录长度的属性
template<typename T>
size_t LinkList<T>::length()
{
    size_t count = 0;
    Link<T>* tmp = head_->next;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

template<typename T>
bool LinkList<T>::Append(const T& value)
{
    Link<T>* tmp = new Link<T>(value);
    if (head_ == tail_)
    {
        head_->next = tmp;
        tail_ = tmp;
    }
    else
    {
        tail_->next = tmp;
        tail_ = tmp;
    }
    return true;
}

template<typename T>
bool LinkList<T>::Insert(const int p, const T& value)
{
    Link<T>* pre;
    if ((pre = SetPos(p - 1)) == nullptr) // pre是第p个结点的前驱
    {
        std::cout << "Insert point is illegal\n";
        return false;
    }
    Link<T>* tmp = new Link<T>(value, pre->next);
    pre->next = tmp;
    if (pre == tail_)
        tail_ = tmp;
    return true;
}

template<typename T>
bool LinkList<T>::Remove(const int p)
{
    Link<T>* pre;
    pre = SetPos(p - 1);
    if (pre == nullptr || pre == tail_)
    {
        std::cout << "Remove point is illegal" << std::endl;
        return false;
    }
    Link<T>* cur;
    cur = pre->next;
    if (cur == tail_)
    {
        tail_ = pre;
        pre->next = nullptr;
        delete cur;
    }
    else if (cur != nullptr)
    {
        pre->next = cur->next;
        delete cur;
    }
    return true;
}

template<typename T>
bool LinkList<T>::GetValue(const int p, T& value)
{
    Link<T>* tmp;
    if ((tmp = SetPos(p)) == nullptr)
    {
        std::cout << "Location is illegal\n";
        return false;
    }
    value = tmp->data;
    return true;
}

template<typename T>
bool LinkList<T>::GetPos(int& p, const T value)
{
    Link<T>* tmp = head_->next;
    int count = -1;
    while (tmp)
    {
        count++;
        if (tmp->data == value)
        {
            p = count;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template<typename T>
void LinkList<T>::ShowAll()
{
    Link<T>* tmp = head_->next;
    while (tmp)
    {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << "\n";
}
