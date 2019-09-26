#include "lianbiaohebing.h"

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int x;
    Ptrtonode next;
} ;

Stack Create()
{
    Stack dummy = (Stack)malloc(sizeof(struct Node));
    if (dummy == NULL) {
        printf("create dummy is wrong, line is %d\n", __LINE__);
    } else {
        dummy->next = NULL;
    }
    return dummy;
}

void InsertBack(int x, Stack dummy)
{
    Ptrtonode tmp = dummy->next;
    while (tmp != NULL) {
        tmp = tmp->next;
    }
    Ptrtonode P = (Ptrtonode)malloc(sizeof(struct Node));
    if (P == NULL) {
        printf("insertback wrong\n");
    } else {
        P->x = x;
        tmp = P;
        P->next = NULL;
    }
}

int main()
{
    Stack dummya = Create();
    for (int i = 0; i < 10; i++) {

    }
    return 0;
}
