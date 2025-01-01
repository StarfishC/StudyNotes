// File:    LinkStack.c
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct SNode* Stack;
struct SNode
{
    ElementType Data;
    Stack Next;
};

// 建立空栈
Stack CreateStack()
{
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->Next = NULL;
    return s;
}

// 判断栈空
int IsEmpty(Stack s)
{
    return s->Next == NULL;
}

// 入栈
void Push(ElementType item, Stack s)
{
    Stack TmpCell;
    TmpCell = (Stack)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = s->Next;
    s->Next = TmpCell;
}

// 出栈
ElementType Pop(Stack s)
{
    Stack first_cell;
    ElementType data;
    if (IsEmpty(s))
    {
        printf("栈空");
        return NULL;
    }
    else
    {
        first_cell = s->Next;
        s->Next = first_cell->Next;
        data = first_cell->Data;
        free(first_cell);
        return data;
    }
}
