// 队列的数组实现，通过在数组中添加一个指定的当前size来避免一些极端情况的发生

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

struct QueueRecord {
    int Capacity;
    int Size;
    int Rear;
    int Front;
    int *Array;
} ; 

Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL) {
        printf("The Q malloc is failed\n");
        exit(1);
    } else {
        Q->Capacity = ARRAYSIZE;
        MakeEmpty(Q);
        Q->Array = (int *)malloc(sizeof(int)*ARRAYSIZE);
    }
    return Q;
}

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

void MakeEmpty(Queue Q)
{
    Q->Rear = 0;
    Q->Front = 1;
    Q->Size = 0;
}

static int succ(int value, Queue Q)
{
    if (++value == Q->Capacity) {
        value = 0;
    }
    return value;
}

void Enqueue(int x, Queue Q)
{
    // 判断当前队列是否是满队列
    if (IsFull(Q)) {
        printf("The queue is full\n");
    } else {
        // 当前队列不是满队列，那么应该判断rear是否已经指向队列的最后一个元素，如果指向最后一个，那么就应该循环数组.
        Q->Size++;
        Q->Rear = succ(Q->Rear, Q);
        Q->Array[Q->Rear] = x;
    }
}

void Dequeue(Queue Q)
{
    if (IsEmpty(Q)) {
        printf("The queue is empty\n");
    } else {
        Q->Size--;
        Q->Front++;
    }
}

int FrontAndDequeue(Queue Q)
{
    int value = Q->Array[Q->Front];
    Dequeue(Q);
    return value;
}
