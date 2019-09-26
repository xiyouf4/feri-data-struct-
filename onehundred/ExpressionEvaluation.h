#ifndef EXPRESSIONEVALUATION_H
#define EXPRESSIONEVALUATION_H

struct Node;
typedef struct Node *Ptrtonode;
typedef Ptrtonode Stack;

typedef enum choice {
    INIT = 1,
    GO,
    EXIT,
} choice_t;

Stack CreateStack(void);
int IsEmpty(Stack S);
void Push(char x, Stack S);
void Pop(Stack S);
char Top(Stack S);
void MakeEmpty(Stack S);

#endif
