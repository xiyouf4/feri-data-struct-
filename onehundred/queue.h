#ifndef QUEUE_H
#define QUEUE_H

#define ARRAYSIZE 10

struct QueueRecord;
typedef struct QueueRecord *Queue;

Queue CreateQueue();
int IsEmpty(Queue Q);
void MakeEmpty(Queue Q);
int IsFull(Queue Q);
void Enqueue(int x, Queue Q);
void Dequeue(Queue Q);
void DisposeQueue(Queue Q);
int Front(Queue Q);
int FrontAndDequeue(Queue Q);

#endif
