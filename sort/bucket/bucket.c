#include "bucket.h"
#include <stdio.h>

int *bucket_sort(const int a[], int len)
{
    int li;
    int num[1000];
    for (int i = 0; i < 1000; i++) {
        num[i] = 0;
    }
    for (int i = 0; i < len; i++) {
        li = a[i];
        num[li]++;
    }
    int *p = num;
    return p;
}

