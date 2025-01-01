// File:    LinkQueue.c
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <stdlib.h>
#include <stdio.h>

#define ERROR -999
typedef int ElementType;

struct Node
{
    ElementType data;
    struct Node* next;
};

typedef struct QNode* Queue;
struct QNode
{
    struct Node* rear;
    struct Node* front;
};

void AddQ(Queue q, ElementType item)
{
    struct Node* tmp_node;
    if (q->front == NULL)
    {
        // 队列没有元素
        tmp_node = (struct Node*)malloc(sizeof(struct Node));
        tmp_node->data = item;
        tmp_node->next = NULL;
        q->front = q->rear = tmp_node;
    }
    else
    {
        // 队列已有元素
        tmp_node = (struct Node*)malloc(sizeof(struct Node));
        tmp_node->data = item;
        tmp_node->next = q->rear;
        q->rear = tmp_node;
    }
}

ElementType DeleteQ(Queue q)
{
    struct Node* front_cell;
    ElementType front_elem;

    if (q->front == NULL)
    {
        printf("队列空");
        return ERROR;
    }
    front_cell = q->front;
    if (q->front == q->rear)
        // 只有一个元素
        q->front = q->rear = NULL;
    else
        q->front = q->front->next;
    front_elem = front_cell->data;
    free(front_cell);
    return front_elem;
}
