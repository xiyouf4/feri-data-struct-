#include "Stack_Array.h"

#include <stdio.h>
#include <stdlib.h>

struct StackRecord {
    int capacity; 
    int TopOfStack;
    int *Array;
} ;

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTos;
}

void MakeEMpty(Stack S)
{
    S->TopOfStack = EmptyTos;
}

void DisposeStack(Stack S)
{
    if (S != NULL) {
        free(S->Array);
        free(S);
    }
}

int IsFull(Stack S)
{
    if (S->TopOfStack+1 == S->capacity) {
        return 0;
    } else {
        return 1;
    }
}

void Push(int x, Stack S)
{
    if (IsFull(S)) {
        printf("Stack is full\n");
        return;
    } else {
        S->Array[++S->capacity] = x;
    }
}

int Top(Stack S){
    if (!IsEmpty(S)) {
        return S->Array[S->TopOfStack--];
    } else {
        printf("Stack is empty\n");
        return 0;
    }
}

void Pop(Stack S)
{
    if (!IsFull(S)) {
        printf("The Stack is full\n");
        return;
    } else {
        S->TopOfStack--;
    }
}

Stack CreateStack(int MaxElements)
{
    Stack S;
    if (MaxElements < MinStackSize) {
        printf("Stack size is to small");
    }
    S = (Stack)malloc(sizeof(struct StackRecord));
    if (S == NULL) {
        printf("init Stack is failed\n");
    }
    S->Array = (int *)malloc(sizeof(int)*MaxElements);
    if (S->Array == NULL) {
        printf("Out of space\n");
    }
    S->capacity = MaxElements;
    MakeEMpty(S);
    return S;
}
