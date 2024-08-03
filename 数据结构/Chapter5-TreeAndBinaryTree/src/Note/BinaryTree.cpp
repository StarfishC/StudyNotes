// File:    BinaryTree.cpp
// Author:  csh
// Date:    2021/4/10
// ===================

#include <stack>
#include <queue>
#include <iostream>

template<typename T>
class BinaryTree;

template<typename T>
class BinaryTreeNode
{
    friend class BinaryTree<T>;

private:
    T info_;
    BinaryTreeNode<T>* left_;
    BinaryTreeNode<T>* right_;

public:
    BinaryTreeNode();
    BinaryTreeNode(const T& ele);
    BinaryTreeNode(const T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r);
    T Value() const; // 返回当前结点的数据
    BinaryTreeNode<T>* LeftChild() const; // 返回当前结点的左子树
    BinaryTreeNode<T>* RightChild() const; // 返回当前结点的右子树
    void SetLeftChild(BinaryTreeNode<T>* pointer); // 设置当前结点的左子树
    void SetRightChild(BinaryTreeNode<T>* pointer); // 设置当前结点的右子树
    void SetValue(const T& value); // 设置当前结点的数据
    bool IsLeaf() const; // 判断当前结点是否为叶结点
    BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& node); // 重载赋值操作符
};

template<typename T>
class BinaryTree
{
private:
    BinaryTreeNode<T>* root_;

public:
    BinaryTree();
    ~BinaryTree() { DeleteBinaryTree(); }
    void DeleteBinaryTree(); // 释放整个二叉树空间
    void deleteBinaryTree(BinaryTreeNode<T>* root); // 删除给定的二叉树
    bool IsEmpty() const; // 判定二叉树是否为空
    BinaryTreeNode<T>* Root(); // 返回二叉树根结点
    BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current); // 返回当前结点的父结点
    BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current); // 返回当前结点的左兄弟
    BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current); // 返回当前结点的右兄弟
    void Create(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree); // 构造新树
    void Visit(const T& val) const; // 访问结点值
    void PreOrder(); // 先序周游二叉树
    void PreOrder(BinaryTreeNode<T>* root); // 先序周游给定二叉树
    void InOrder(); // 中序周游二叉树
    void InOrder(BinaryTreeNode<T>* root); // 中序周游给定二叉树
    void PostOrder(); // 后序周游二叉树
    void PostOrder(BinaryTreeNode<T>* root); // 后序周游给定二叉树
    void LevelOrder(); // 层次周游二叉树
    void PreOrderWithoutRecursion(); // 先序周游二叉树，非递归
    void InOrderWithoutRecursion(); // 中序周游二叉树，非递归
    void PostOrderWithoutRecursion(); // 后序周游二叉树，非递归
};

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode() :
    BinaryTreeNode<T>(0, nullptr, nullptr)
{
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele) :
    BinaryTreeNode<T>(ele, nullptr, nullptr)
{
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) :
    info_(ele), left_(l), right_(r)
{
}

template<typename T>
inline T BinaryTreeNode<T>::Value() const
{
    return info_;
}

template<typename T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::LeftChild() const
{
    return left_;
}

template<typename T>
inline BinaryTreeNode<T>* BinaryTreeNode<T>::RightChild() const
{
    return right_;
}

template<typename T>
inline void BinaryTreeNode<T>::SetLeftChild(BinaryTreeNode<T>* pointer)
{
    left_ = pointer;
}

template<typename T>
inline void BinaryTreeNode<T>::SetRightChild(BinaryTreeNode<T>* pointer)
{
    right_ = pointer;
}

template<typename T>
inline void BinaryTreeNode<T>::SetValue(const T& value)
{
    info_ = value;
}

template<typename T>
bool BinaryTreeNode<T>::IsLeaf() const
{
    return left_ == nullptr && right_ == nullptr;
}

template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& node)
{
    info_ = node.Value();
    left_ = node.LeftChild();
    right_ = node.RightChild();
    return *this;
}

template<typename T>
BinaryTree<T>::BinaryTree() :
    root_(nullptr)
{
}

template<typename T>
void BinaryTree<T>::DeleteBinaryTree()
{
    DeleteBinaryTree(root_);
}

template<typename T>
void BinaryTree<T>::deleteBinaryTree(BinaryTreeNode<T>* root)
{
    if (root)
    {
        DeleteBinaryTree(root->LeftChild());
        DeleteBinaryTree(root->RightChild());
        delete root;
    }
}

template<typename T>
void BinaryTree<T>::Create(const T& info, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree)
{
    root_ = new BinaryTreeNode<T>(info, leftTree.Root(), rightTree.Root());
    leftTree.Root() = rightTree.Root() = nullptr;
}

template<typename T>
inline bool BinaryTree<T>::IsEmpty() const
{
    return root_ == nullptr;
}

template<typename T>
inline BinaryTreeNode<T>* BinaryTree<T>::Root()
{
    return root_;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
{
    // 采用先序周游思想
    using std::stack;
    stack<BinaryTreeNode<T>*> node_stack;
    BinaryTreeNode<T>* pointer = root_;
    if (current == nullptr || current == root_)
        return nullptr;
    node_stack.push(nullptr); // 栈底监视哨
    while (pointer)
    {
        if (current == pointer->LeftChild() || current == pointer->RightChild())
            return pointer;
        if (pointer->RightChild())
            node_stack.push(pointer->RightChild());
        if (pointer->LeftChild())
            pointer = pointer->LeftChild();
        else
        {
            pointer = node_stack.top();
            node_stack.pop();
        }
    }
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::LeftSibling(BinaryTreeNode<T>* current)
{
    BinaryTreeNode<T>* ret = Parent(current);
    if (ret)
        return ret->LeftChild();
    return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::RightSibling(BinaryTreeNode<T>* current)
{
    BinaryTreeNode<T>* ret = Parent(current);
    if (ret)
        return ret->RightChild();
    return nullptr;
}

template<typename T>
void BinaryTree<T>::Visit(const T& val) const
{
    using std::cout;
    cout << val << " ";
}

template<typename T>
void BinaryTree<T>::PreOrder()
{
    PreOrder(root_);
}

template<typename T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root)
{
    if (root)
    {
        Visit(root->Value());
        PreOrder(root->LeftChild());
        PreOrder(root->RightChild());
    }
}

template<typename T>
void BinaryTree<T>::InOrder()
{
    InOrder(root_);
}

template<typename T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root)
{
    if (root)
    {
        InOrder(root->LeftChild());
        Visit(root->Value());
        InOrder(root->RightChild());
    }
}

template<typename T>
void BinaryTree<T>::PostOrder()
{
    PostOrder(root_);
}

template<typename T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root)
{
    if (root)
    {
        PostOrder(root->LeftChild());
        PostOrder(root->RightChild());
        Visit(root->Value());
    }
}

template<typename T>
void BinaryTree<T>::PreOrderWithoutRecursion()
{
    using std::stack;
    stack<BinaryTreeNode<T>*> node_stack;
    BinaryTreeNode<T>* pointer = root_;
    node_stack.push(nullptr); // 栈底监视哨
    while (pointer)
    {
        Visit(pointer->Value());
        if (pointer->RightChild())
            node_stack.push(pointer->RightChild());
        if (pointer->LeftChild())
            pointer = pointer->LeftChild();
        else
        {
            pointer = node_stack.top();
            node_stack.pop();
        }
    }
}

template<typename T>
void BinaryTree<T>::InOrderWithoutRecursion()
{
    using std::stack;
    stack<BinaryTreeNode<T>*> node_stack;
    BinaryTreeNode<T>* pointer = root_;
    while (!node_stack.empty() || pointer)
    {
        if (pointer)
        {
            node_stack.push(pointer);
            pointer = pointer->LeftChild();
        }
        else
        {
            pointer = node_stack.top();
            node_stack.pop();
            Visit(pointer->Value());
            pointer = pointer->RightChild();
        }
    }
}

enum class Tags
{
    kLeft,
    kRight
};
template<typename T>
class StackElement
{
public:
    BinaryTreeNode<T>* pointer;
    Tags tag;
};
template<typename T>
void BinaryTree<T>::PostOrderWithoutRecursion()
{
    using std::stack;
    stack<StackElement<T>*> element_stack;
    StackElement<T> element;
    BinaryTreeNode<T>* pointer = root_;
    while (!element_stack.empty() || pointer)
    {
        while (pointer) // 当前指针非空则压栈并下降到最左子结点
        {
            element.pointer = pointer;
            element.tag = Tags::kLeft; // 标记为Left
            element_stack.push(element);
            pointer = pointer->LeftChild();
        }
        element = element_stack.top();
        element_stack.pop();
        pointer = element.pointer;
        if (element.tag == Tags::kLeft) // 标记是Left，表示右子树未压栈
        {
            element.tag = Tags::kRight; // 置标记为Right
            element_stack.push(element);
            pointer = pointer->RightChild();
        }
        else
        {
            Visit(pointer->Value());
            pointer = nullptr;
        }
    }
}

template<typename T>
void BinaryTree<T>::LevelOrder()
{
    using std::queue;
    queue<BinaryTreeNode<T>*> node_queue;
    BinaryTreeNode<T>* pointer = root_;
    if (pointer)
        node_queue.push_back(pointer);
    while (!node_queue.empty())
    {
        pointer = node_queue.front();
        node_queue.pop_front();
        Visit(pointer->Value());
        if (pointer->LeftChild())
            node_queue.push_back(pointer->LeftChild());
        if (pointer->RightChild())
            node_queue.push_back(pointer->RightChild());
    }
}
