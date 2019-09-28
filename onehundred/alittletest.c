#include <stdio.h>
#include <stdlib.h>

struct Node {
    int a;
    int b;
} ; 

typedef struct Node *node;

int add(node n)
{
    int d = ++n->a;
    return d;
}

int main()
{
    node n = (node)malloc(sizeof(struct Node));
    n->a = 0;
    n->b = 1;
    int c = add(n);
    printf("%d\n", c);
    printf("%d\n", n->a);
    return 0;
}

