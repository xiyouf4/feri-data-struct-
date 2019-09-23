#include "radix.h"
#include <stdio.h>

int main()
{
    int a[999];
    int k = 999;
    for (int i = 0; i < 999; i++) {
        a[i] = k;
        k--;
    }
    int *p = radix_sort(a, 999);
    for (int i = 0; i < 999; i++) {
        printf("%d\t", *p);
        p++;
    }
    return 0;
}

