// File:    父指针表示与并查集算法.cpp
// Author:  csh
// Date:    2020/09/12
// ===================

template<typename T>
class ParTreeNode
{
private:
    T value_;
    ParTreeNode<T>* parent_; // 父结点指针
    int count_; // 子树元素数目
public:
    ParTreeNode();
    ~ParTreeNode() {}
    T GetValue(); // 返回结点的值
    void SetValue(const T& val); // 设置结点的值
    ParTreeNode<T>* GetParent(); // 返回父结点指针
    void SetParent(ParTreeNode<T>* par); // 设置父结点指针
    int GetCount(); // 返回结点数目
    void SetCount(const int count); // 设置结点数目
};

template<typename T>
class ParTree
{
public:
    ParTreeNode<T>* array; // 存储树结点的数组
    int size; // 数组大小

    ParTree(const int num);
    ~ParTree(); // 析构函数
    ParTreeNode<T>* Find(ParTreeNode<T>* node) const; // 查找node结点的根结点
    ParTreeNode<T>* FindPC(ParTreeNode<T>* node) const; // 路径压缩，返回当前结点的根结点，
        // 并将当前结点的所有祖先结点的父指针指向根结点
    void Union(int i, int j); // 把下标为i,j的结点合并成一颗子树
    bool Different(int i, int j); // 判断结点i,j是否有相同的根结点
};

template<typename T>
ParTreeNode<T>* ParTree<T>::Find(ParTreeNode<T>* node) const
{
    ParTreeNode<T>* pointer = node;
    while (pointer->GetParent() != nullptr)
        pointer = pointer->GetParent();
    return pointer;
}

template<typename T>
bool ParTree<T>::Different(int i, int j)
{
    ParTreeNode<T>* pointer_i = Find(&array[i]);
    ParTreeNode<T>* pointer_j = Find(&array[j]);
    return pointer_i == pointer_j;
}

template<typename T>
void ParTree<T>::Union(int i, int j)
{
    ParTreeNode<T>* pointer_i = Find(&array[i]);
    ParTreeNode<T>* pointer_j = Find(&array[j]);
    if (pointer_i != pointer_j)
    {
        if (pointer_i->GetCount() >= pointer_j->GetCount())
        {
            pointer_j->SetParent(pointer_i);
            pointer_i->SetCount(pointer_i->GetCount() + pointer_j->GetCount());
        }
        else
        {
            pointer_i->SetParent(pointer_j);
            pointer_j->SetCount(pointer_j->GetCount() + pointer_i->GetCount());
        }
    }
}

template<typename T>
ParTreeNode<T>* ParTree<T>::FindPC(ParTreeNode<T>* node) const
{
    if (node->GetParent() == nullptr)
        return node;
    node->SetParent(FindPC(node->GetParent()));
    return node->GetParent();
}
