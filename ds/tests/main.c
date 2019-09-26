/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

#include <stdio.h>
#include "darray.h"

int total(void *ctx, void *data)
{
    int *sum = (int *)ctx;
    printf("%lu\n", (unsigned long) data);
    *sum += (unsigned long)data;

    return OK;
}

void test_darray()
{
    //64位环境，(void *)占8个字节
    unsigned long i = 0, n = 10;
    DArray *darray = darrayCreate(NULL, NULL);

    for (i = 0; i < n; i++) {
        darrayPrepend(darray, (void *)(2 *i));
        darrayAppend(darray, (void *)i);
    }

    unsigned long sum = 0;
    darrayForeach(darray, total, &sum);
    printf("sum: %lu\n", sum);
    darrayRelease(darray);
}

int main(int argc, char *argv[])
{
    test_darray();
    return 0;
}

