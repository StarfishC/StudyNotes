// File:    ArrList.hpp
// Author:  csh
// Date:    2021/02/20
// Update:  2024/12/07
// ===================

#include <cstdlib>
#include <iostream>

template<typename T>
class ArrList
{
public:
    ArrList(const size_t size);
    ~ArrList();
    void Clear(); // 清楚顺序表内容，成为空表
    size_t Length(); // 返回顺序表的长度
    bool Empty(); // 判断线性表是否为空
    bool Full(); // 判断线性表是否已满
    bool Append(const T& value); // 表尾添加一个元素
    bool Insert(const int p, const T& value); // 位置P插入一个元素
    bool Remove(const int p); // 移除位置p上的元素
    bool SetValue(const int p, const T& value); // 修改位置p的元素值
    bool GetValue(const int p, T& value); // 返回位置p的元素给value
    bool GetPos(const T& value, int& p); // 查找指为value的元素，并返回位置给p
    void ShowAll(); // 显示所有元素
private:
    T* list_; // 存储顺序表的数组
    size_t max_size_; // 顺序表的最大长度
    size_t cur_len_; // 顺序表的当前长度
};

template<typename T>
ArrList<T>::ArrList(const size_t size):
    list_(new T[size]), max_size_(size), cur_len_(0) {}

template<typename T>
ArrList<T>::~ArrList()
{
    delete[] list_;
}

template<typename T>
inline void ArrList<T>::Clear()
{
    cur_len_ = 0;
}

template<typename T>
inline size_t ArrList<T>::Length()
{
    return cur_len_;
}

template<typename T>
inline bool ArrList<T>::Empty()
{
    return cur_len_ == 0;
}

template<typename T>
inline bool ArrList<T>::Full()
{
    return cur_len_ >= max_size_;
}

template<typename T>
bool ArrList<T>::Append(const T& value)
{
    if (Full())
    {
        std::cout << "The list is overflow" << std::endl;
        return false;
    }
    list_[cur_len_++] = value;
    return true;
}

template<typename T>
bool ArrList<T>::Insert(const int p, const T& value)
{
    if (Full())
    {
        std::cout << "The list is overflow" << std::endl;
        return false;
    }
    if (p < 0 || p > cur_len_)
    {
        std::cout << "Insert point is illegal" << std::endl;
        return false;
    }
    for (int i = cur_len_; i > p; i--)
        list_[i] = list_[i-1];
    list_[p] = value;
    cur_len_++;
    return true;
}

template<typename T>
bool ArrList<T>::Remove(const int p)
{
    if (Empty())
    {
        std::cout << "No element to remove" << std::endl;
        return false;
    }
    if (p < 0 || p > cur_len_)
    {
        std::cout << "Remove point is illegal" << std::endl;
        return false;
    }
    for (int i = p; i < cur_len_-1; i++)
        list_[p] = list_[i+1];
    cur_len_--;
    return false;
}

template<typename T>
bool ArrList<T>::SetValue(const int p, const T& value)
{
    if (p < 0 || p >= cur_len_)
    {
        std::cout << "Location is illegal" << std::endl;
        return false;
    }
    list_[p] = value;
    return true;
}

template<typename T>
bool ArrList<T>::GetValue(const int p, T& value)
{
    if (p < 0 || p >= cur_len_)
    {
        std::cout << "Location is illegal" << std::endl;
        return false;
    }
    value = list_[p];
    return true;
}

template<typename T>
bool ArrList<T>::GetPos(const T& value, int& p)
{
    for (int i = 0; i < cur_len_; i++)
    {
        if (value == list_[i])
        {
            p = i;
            return true;
        }
    }
    return false;
}
