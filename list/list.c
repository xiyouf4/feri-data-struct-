#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct Node {
    ElementType Element;
    Position Next;
};

int IsEmpety(List L)
{
    int r;
    if (L->Next == NULL) {
        r = 0;
    } else {
        r = -1;
    }
    return r;
}

int IsLast(Position P)
{
    int r;
    if (P->Next == NULL) {
        r = 0;
    } else {
        r = -1;
    }
    return r;
}

Position Find(ElementType x, List L)
{
    Position p = L->Next;
    while (p->Element != x && p!=NULL) {
        p = p->Next;
    }
    return p;
}

Position FindPrevious(ElementType x, List L)
{
    Position p = L;
    while (p->Next->Element != x && p->Next != NULL) {
        p = p->Next;
    }
    return p;
}

void Delete(ElementType x, List L)
{
    Position p, temp;
    p = FindPrevious(x, L);
    if (!IsLast(p)) {
        temp = p->Next;      
        p->Next = temp->Next;
        free(temp);          
    } 
}

void InsertBack(ElementType x, Position P)
{
    Position temp = (PtrToNode)malloc(sizeof(Node));
    temp->Element = x;
    temp->Next = P->Next;
    P->Next = temp;
}

void Insertfront(ElementType x, List L, Position P)
{
    Position p = FindPrevious(P->Element, L);
    Position temp = (PtrToNode)malloc(sizeof(Node));
    temp->Element = x;
    temp->Next = P;
    p->Next = temp;
}

void DeleteList(List L)
{
    Position p, tmp;
    p = L->Next;
    L->Next = NULL;
    while (p != NULL) {
        tmp = p->Next;
        free(p);
        p = tmp;
    }
}

List MakeEmpty(List L)
{
    Position temp = L->Next;
    while (temp != NULL) {
        temp->Element = 0;
        temp = temp ->Next;
    }
    return L;
}

void DeleteElement(List L, ElementType x)
{
    Position pn = Find(x, L);
    Position ps = FindPrevious(x, L);
    ps->Next = pn->Next;
    free(pn);
}

void ChangeElement(List L, ElementType x, ElementType y)
{
    Position pn = Find(x, L);
    pn->Element = y;
}









