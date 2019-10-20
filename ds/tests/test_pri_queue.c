/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-20
 */

#include "priority_queue.h"

int greater(ElemType a, ElemType b)
{
    if ((int)a > (int)b) {
        return 1;
    } else {
        return 0;
    }
}

int less(ElemType a, ElemType b)
{
    if ((int)a < (int)b) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    PriorityQueue *queue = priorityQueueCreate(greater);
    int i;
    int a[] = {10, 8, 12, 14, 6};
    int a_len = sizeof(a) / sizeof(a[0]);
    for (i = 0; i < a_len; i++) {
        priorityQueuePush(queue, (ElemType) a[i]);
    }

    while (!priorityQueueEmpty(queue)) {
        ElemType out_val;
        priorityQueuePop(queue, &out_val);
        printf("%d ", (int) out_val);
    }

    printf("\n");
}

