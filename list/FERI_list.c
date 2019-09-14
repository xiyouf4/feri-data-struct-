#include "FERI_list.h"

#include <stdlib.h>
/*创建一个链表的哑结点*/
feri_list *listcreate(void)
{
    struct feri_list *list;
    if ((list = (feri_list *)malloc(sizeof(*list))) == NULL) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    return list;
}
/*头插*/
feri_list *listaddnodehead(feri_list *list, void *value)
{
    feri_listnode *node;
    if ((node = (feri_listnode *)malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->value = value;
    if (list->len == 0) {
        list->head = list->tail = node;
        node->pre = node->nex = NULL;
    } else {
        node->pre = NULL;
        node->nex = list->head;
        list->head->pre = node;
        list->head = node;
    }
    list->len++;
    return list;
}
/*尾插*/
feri_list *listaddnodetail(feri_list *list, void *value)
{
    feri_listnode *node;
    if ((node = (feri_listnode *)malloc(sizeof(*node))) == NULL) {
        return NULL;
    } else {
        node->value = value;
        if (list->len == 0) {
            list->head = list->tail = node;
            node->nex = node->pre = NULL;
        } else {
            node->pre = list->tail;
            node->nex = NULL;
            list->tail->nex = node;
            list->tail = node;
        }
        list->len++;
    }
    return list;
}
/*迭代器条件控制，从头开始遍历*/
void listrewindhead(feri_list *list, feri_iter *li)
{
    li->next = list->head;
    li->direction = FERI_START_HEAD;
}
/*迭代器条件控制，从尾开始遍历*/
void listrewindtail(feri_list *list, feri_iter *li)
{
    li->next = list->tail;
    li->direction = FERI_START_TAIL;
}
/*迭代器控制临时索引结点向下一个结点跳转*/
feri_listnode *listnext(feri_iter *iter)
{
    feri_listnode *current = iter->next;
    if (current != NULL) {
        if (iter->direction == FERI_START_HEAD) {
            iter->next = current->nex;
        } else if (iter->direction == FERI_START_TAIL) {
            iter->next = current->pre;
        }
    }
    return current;
}
/*在某一个链表中查找*/
feri_listnode *listfindkey(feri_list *list, void *key)
{
    feri_listnode *node;
    feri_iter iter;
    listrewindhead(list, &iter);
    while ((node = listnext(&iter)) != NULL) {
        if (list->match) {
            if (1/*list->match(node->value, key)*/) {//void类型的值不能在上下文中转换为bool类型的值？？？？？？？？？？？
                return node;
            }
        } else {
            if (key == node->value) {
                return node;
            }
        }
    }
    return NULL;
}
/*在链表中插入*/
feri_list *listinsertnode(feri_list *list, feri_listnode *old_node, void *value, int after)
{
    feri_listnode *node;
    if ((node = (feri_listnode *)malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->value = value;
    if (after == 0) {//前叉
        node->nex = old_node;
        node->pre = old_node->pre;
        if (list->head == old_node) {
            list->head = node;
        }
    } else if (after == 1) {
        node->pre = old_node;
        node->nex = old_node->nex;
        if (list->tail == old_node) {
            list->tail = old_node;
        }
    }
    if (node->pre != NULL) {
        node->pre->nex = node;
    }
    if (node->nex != NULL) {
        node->nex->pre = node;
    }
    list->len++;
    return list;
}
/*删除链表中的某一个结点*/
void listdelnode(feri_list *list, feri_listnode *node)
{
    if (node->pre) {
        node->pre->nex = node->nex;
    } else {
        list->head = node->nex;
        node->nex->pre = NULL;
    }
    if (node->nex) {
        node->nex->pre = node->pre;
    } else {
        list->tail = node->pre;
        node->pre->nex = NULL;
    }
    if (list->free) {
        list->free(node->value);/////////////////////////////////////////////////////////////////////
    }
    free(node);
    list->len--;
}

void listempty(feri_list *list){
    unsigned long len = list->len;
    feri_listnode *current,*tmp;
    current = list->head;
    while (len--) {
        tmp = current->nex;
        if (list->free) {
            list->free(current->value);
        }
        free(current);
        current = tmp;
    }
    list->head = list->tail = NULL;
    list->len = 0;
}

void listrelease(feri_list *list)
{
    listempty(list);
    free(list);
}
/*改变某一个结点的内容*/
feri_list *listchangenode(feri_list *list, feri_listnode *node, void *value)
{
    node->value = value;
    return list;
}
