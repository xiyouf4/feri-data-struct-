#ifndef _LIST_H
#define ElementType int
struct Node;
typedef struct Node *PtrToNode;//声明了一个类型，该类型是指向Node类型结构体的指针
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);//
int IsEmpty(List L);//
int IsLast(Position p);//
Position Find(ElementType x, List L);
void Delete(ElementType x, List L);//
Position FindPrevious(ElementType x, List L);//
void InsertBack(ElementType x, Position P);//
void Insertfront(ElementType x, List L, Position P);//
void DeleteList(List L);//
void DeleteElement(List L, ElementType x);//
void ChangeElement(List L, ElementType x, ElementType y);//
#endif
