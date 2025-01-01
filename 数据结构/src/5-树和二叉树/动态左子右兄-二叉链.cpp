// File:    动态左子右兄-二叉链.cpp
// Author:  csh
// Date:    2020/09/20
// ===================

#include <stack>
#include <queue>
#include <iostream>

template<typename T>
class TreeNode
{
private:
    T value_;
    TreeNode<T>* child_; // 左子结点
    TreeNode<T>* sibling_; // 右兄弟指针
public:
    TreeNode(const T& v);
    ~TreeNode() {}
    bool IsLeaf(); // 判断是否为叶结点
    T Value(); // 返回结点的值
    TreeNode<T>* LeftMostChild(); // 返回第一个左节点
    TreeNode<T>* RigthSibling(); // 返回右兄弟
    void SetValue(const T& v); // 设置当前节点的值
    void SetChild(TreeNode<T>* node); // 设置左子结点
    void SetSibling(TreeNode<T>* node); // 设置右兄弟
    void InsertFirst(TreeNode<T>* node); // 以第一个结点身份插入结点
    void InsertNext(TreeNode<T>* node); // 以有兄弟身份插入结点
};

template<typename T>
TreeNode<T>::TreeNode(const T& v) :
    value_(v), child_(nullptr), sibling_(nullptr)
{
}

template<typename T>
inline bool TreeNode<T>::IsLeaf()
{
    return child_ == nullptr;
}

template<typename T>
inline T TreeNode<T>::Value()
{
    return value_;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::LeftMostChild()
{
    return child_;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::RigthSibling()
{
    return sibling_;
}

template<typename T>
inline void TreeNode<T>::SetValue(const T& v)
{
    value_ = v;
}

template<typename T>
inline void TreeNode<T>::SetChild(TreeNode<T>* node)
{
    child_ = node;
}

template<typename T>
inline void TreeNode<T>::SetSibling(TreeNode<T>* node)
{
    sibling_ = node;
}

template<typename T>
void TreeNode<T>::InsertFirst(TreeNode<T>* node)
{
    if (child_ == nullptr) // 如果没有子结点
        child_ = node;
    else
    {
        node->SetSibling(child_); // 有子结点，原来子结点置为node的右兄弟
        child_ = node;
    }
}

template<typename T>
void TreeNode<T>::InsertNext(TreeNode<T>* node)
{
    if (!sibling_)
        sibling_ = node;
    TreeNode<T>* temppointer = sibling_;
    while (temppointer->rigthSibling()) // 找到最右边右兄弟
        temppointer = temppointer->rigthSibling();
    temppointer->SetSibling(node);
}

template<typename T>
class Tree
{
private:
    TreeNode<T>* root_;

public:
    Tree() :
        root_(nullptr) {}
    ~Tree();
    TreeNode<T>* GetRoot();
    void CreateRoot(const T& rootValue); // 创建值为rootValue的根结点
    bool IsEmpty(); // 判断是否为空树
    TreeNode<T>* Parent(TreeNode<T>* current); // 返回当前结点父结点
    TreeNode<T>* PrevSibling(TreeNode<T>* current); // 返回当前结点的前一个兄弟
    void DeleteSubTree(TreeNode<T>* subroot); // 删除以subroot为根的子树
    void DeleteNodes(TreeNode<T>* node);
    void RootFirstTraverse(TreeNode<T>* root); // 先根深度优先周游
    void RootFirstTraverse();
    void RootLastTraverse(TreeNode<T>* root); // 后根深优先周游
    void RootLastTraverse();
    void WidthTraverse(); // 广度优先周游
    void Visit(T& value);
};

template<typename T>
inline TreeNode<T>* Tree<T>::GetRoot()
{
    return root_;
}

template<typename T>
inline bool Tree<T>::IsEmpty()
{
    return root_ == nullptr;
}

template<typename T>
TreeNode<T>* Tree<T>::Parent(TreeNode<T>* current)
{
    using std::queue;
    queue<TreeNode<T>*> node_queue;
    TreeNode<T>* pointer = root_;
    TreeNode<T>* upperlevelpointer = nullptr; // 用于记录父结点
    if (current != nullptr && pointer != current)
    {
        while (pointer)
        { // 森林中所有的根结点入队
            if (current == pointer)
                return nullptr;
            node_queue.push_back(pointer);
            pointer = pointer->RigthSibling(); // 指向右兄弟，继续入队
        }
        while (!node_queue.empty())
        {
            pointer = node_queue.front();
            node_queue.pop_front();
            upperlevelpointer = pointer;
            pointer = pointer->LeftMostChild(); // 指向当前结点最左子结点
            while (pointer)
            {
                if (current == pointer)
                    return upperlevelpointer;
                else
                {
                    node_queue.push_back(pointer);
                    pointer = pointer->RigthSibling();
                }
            }
        }
    }
    return nullptr;
}

template<typename T>
void Tree<T>::DeleteSubTree(TreeNode<T>* subroot)
{
    TreeNode<T>* pointer;
    if (subroot == nullptr)
        return;
    pointer = Parent(subroot);
    if (pointer == nullptr) // subroot就是森林第一个树根情况
        root_ = subroot->rigthSibling(); // 将treeRoot设置为subroot有兄弟
    else if (pointer->LeftMostChild() == subroot) // subroot为最左子结点情况
        pointer->SetChild(subroot->RigthSibling()); // pointer的左子结点置为subroot的右兄弟
    else
    { // 有左兄弟的情况
        pointer = pointer->LeftMostChild();
        while (pointer->RigthSibling() != subroot)
            pointer = pointer->RigthSibling();
        pointer->SetSibling(subroot->RigthSibling());
    }
    subroot->SetSibling(nullptr);
    DeleteNodes(subroot);
}

template<typename T>
void Tree<T>::DeleteNodes(TreeNode<T>* node)
{
    if (node)
    {
        DeleteNodes(node->LeftMostChild());
        DeleteNodes(node->RigthSibling());
        delete node;
    }
}

template<typename T>
void Tree<T>::Visit(T& value)
{
    using std::cout;
    cout << value << " ";
}

template<typename T>
void Tree<T>::RootFirstTraverse()
{
    RootLastTraverse(root_);
}

template<typename T>
void Tree<T>::RootFirstTraverse(TreeNode<T>* root)
{
    if (root)
    {
        Visit(root->Value());
        RootFirstTraverse(root->LeftMostChild());
        RootFirstTraverse(root->RigthSibling());
    }
}

template<typename T>
void Tree<T>::RootLastTraverse(TreeNode<T>* root)
{
    while (root)
    {
        RootLastTraverse(root->LeftMostChild());
        Visit(root->Value());
        root = root->RigthSibling();
    }
}

template<typename T>
void Tree<T>::RootLastTraverse()
{
    RootLastTraverse(root_);
}

template<typename T>
void Tree<T>::WidthTraverse()
{
    using std::queue;
    queue<TreeNode<T>*> node_queue;
    TreeNode<T>* pointer = root_;
    while (pointer != nullptr)
    {
        node_queue.push_back(pointer);
        pointer = pointer->RigthSibling();
    }
    while (!node_queue.empty())
    {
        pointer = node_queue.front();
        node_queue.pop_front();
        Visit(pointer->Value());
        pointer = pointer->LeftMostChild();
        while (pointer)
        {
            node_queue.push_back(pointer);
            pointer = pointer->RigthSibling();
        }
    }
}
