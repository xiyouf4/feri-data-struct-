#include "bucket.h"
#include <stdio.h>

int main()
{
    int a[6] = {5, 4, 7, 2, 2, 3};
    int *p = bucket_sort(a, 6);
    int num;
    for (int i = 0; i < 10; i++) {
        num = *p;
        if (*p != 0) {
            while (num--) {
                printf("%d\n", i);
            }
            p++;
        } else {
            p++;
            continue;
        }
    }
    return 0;
}

