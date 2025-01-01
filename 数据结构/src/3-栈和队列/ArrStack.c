// File:    ArrStack.c
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 100
#define ERROR -100

typedef int ElementType;

typedef struct SNode* Stack;
struct SNode
{
    ElementType Data[MAXSIZE];
    int Top;
};

Stack CreateStack()
{
    Stack s = (Stack)malloc(sizeof(struct SNode));
    s->Top = -1;
    return s;
}

void Push(Stack ptr, ElementType item)
{
    if (ptr->Top == MAXSIZE - 1)
        printf("栈满\n");
    else
        ptr->Data[++(ptr->Top)] = item;
}

ElementType Pop(Stack ptr)
{
    if (ptr->Top == -1)
    {
        printf("栈空");
        return ERROR; // ERROR是ElementType特殊值，标志错误
    }
    else
    {
        return (ptr->Data[ptr->Top--]);
    }
}
