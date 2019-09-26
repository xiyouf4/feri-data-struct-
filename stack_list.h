#ifndef STACK_LIST_H
#define STACK_LIST_H

struct Node;
typedef struct Node *PtrNode;//声明了一个名为PtrNode的类型，该类型是指向结构体Node的指针
typedef PtrNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(void);
void MakeEmpty(Stack S);
void Push(int x, Stack S);
void pop(Stack S);
int Top(Stack S);

#endif
