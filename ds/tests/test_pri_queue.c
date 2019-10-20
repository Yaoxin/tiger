/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-20
 */

#include "priority_queue.h"

int int_greater(ElemType a, ElemType b)
{
    if ((int) a > (int) b) {
        return 1;
    } else {
        return 0;
    }
}

int int_lesser(ElemType a, ElemType b)
{
    if ((int) a < (int) b) {
        return 1;
    } else {
        return 0;
    }
}

void test_priority_queue()
{
    PriorityQueue *queue = priorityQueueCreate(int_greater);
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

    priorityQueueRelease(queue);
}

int main(int argc, char *argv[])
{
    test_priority_queue();
}

