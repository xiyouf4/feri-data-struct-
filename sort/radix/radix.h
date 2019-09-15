#ifndef RADIX_H
#define RADIX_H

#define NUM_LEN 10

typedef struct value {
    int bucket_num;
    int num[NUM_LEN];
    int numi;
} value_t;            

typedef struct node {  
    value_t *value;       
    struct node *next;
} node_t;              

int *radix_sort(int a[], int len);

#endif
