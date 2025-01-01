// File:    ArrQueue.c
// Author:  csh
// Date:    2021/02/21
// Update:  2024/12/15
// ===================

#include <stdio.h>
#include <stdlib.h>

#define ERROR -999
#define MAXSIZE 100

typedef int ElementType;

typedef struct QNode* Queue;
struct QNode
{
    ElementType Data[MAXSIZE];
    int rear;
    int front;
};

Queue CreateQueue()
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->front = q->rear = 0;
    return q;
}

void AddQ(Queue q, ElementType item)
{
    if ((q->rear + 1) % MAXSIZE == q->front)
    {
        printf("队列满\n");
        return;
    }
    q->Data[q->rear] = item;
    q->rear = (q->rear + 1) % MAXSIZE;
}

ElementType DeleteQ(Queue q)
{
    if (q->front == q->rear)
    {
        printf("队列空");
        return ERROR;
    }
    else
    {
        ElementType item = q->Data[q->front];
        q->front = (q->front + 1) % MAXSIZE;
        return item;
    }
}
