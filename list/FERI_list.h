#ifndef FERI_LIST_H
#define FERI_LIST_H
/*普通结点*/
typedef struct feri_listnode {
    struct feri_listnode *pre;
    struct feri_listnode *nex;
    void *value;
} feri_listnode;
/*迭代器*/
typedef struct feri_iter {
    feri_listnode *next;
    int direction;
} feri_iter;
/*哑结点，本篇博文仅仅使用到了前三项，至于后面的三个函数指针的功能将在下一篇博文中详细解释*/
typedef struct feri_list {
    feri_listnode *head;
    feri_listnode *tail;
    unsigned long len;
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    void (*match)(void *ptr, void *key);
} feri_list;

feri_list *listcreate(void);
feri_list *listaddnodehead(feri_list *list, void *value);
feri_list *listaddnodetail(feri_list *list, void *value);
void listrewindhead(feri_list *list, feri_iter *li);
void listrewindtail(feri_list *list, feri_iter *li);
feri_listnode *listnext(feri_iter *iter);
feri_listnode *listfindkey(feri_list *list, void *key);
feri_list *listinsertnode(feri_list *list, feri_listnode *old_node, void *value, int after);
void listdelnode(feri_list *list, feri_listnode *node);
void listrelease(feri_list *list);//删除该链表包括哑结点
void listempty(feri_list *list);//清空链表，但是哑结点还在
feri_list *listchangenode(feri_list *list, feri_listnode *node, void *value);

#define FERI_START_HEAD 0
#define FERI_START_TAIL 1

#endif
