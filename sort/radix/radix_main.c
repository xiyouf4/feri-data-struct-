#include "radix.h"
#include <stdio.h>

int main()
{
    int a[10] = {1, 200, 500, 999, 31, 30, 39, 5, 6, 28};
    int *p = radix_sort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", *p);
        p++;
    }
    return 0;
}

