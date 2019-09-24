#include "stack_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node {
    int Element;
    PtrNode Next;
} ;

void FeriError(const char *string)
{                                 
    printf("%s", string);         
}                                 

int IsEmpty(Stack S)       
{                          
    return S->Next == NULL;
}                          

void Pop(Stack S)
{
    if (IsEmpty(S)) {
        FeriError("pop's stack is kong\n");
    } else {
        PtrNode tmp = S->Next;
        S->Next = tmp->Next;  
        free(tmp);            
    }
}

void Push(int x, Stack S)
{
    PtrNode tmp = (PtrNode)malloc(sizeof(struct Node));
    if (tmp == NULL) {
        FeriError("push wrong\n");
    } else {
        tmp->Element = x;
        tmp->Next = S->Next;
        S->Next = tmp;
    }
}

int Top(Stack S)
{
    if (!IsEmpty(S)) {
        return S->Next->Element;
    }
    FeriError("stack is kong\n");
    return 0;
}

void MakeEmpty(Stack S)
{
    if (S == NULL) {
        FeriError("S is NULL\n");
    } else {
        while (!IsEmpty(S)) {
            Pop(S);
        }
    }
}

Stack CreateStack(void)
{
    Stack dummy = (Stack)malloc(sizeof(struct Node));
    if (dummy == NULL) {
        FeriError("out of space!!!\n");
    }
    dummy->Next = NULL;
    MakeEmpty(dummy);
    return dummy;
}
