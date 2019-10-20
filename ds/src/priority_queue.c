/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-20
 */

#include <stdlib.h>
#include "priority_queue.h"

PriorityQueue *priorityQueueCreate(ElemComp comp)
{
    PriorityQueue *queue = (PriorityQueue *) calloc(1, sizeof(PriorityQueue));
    if (queue != NULL) {
        queue->heap = minHeapCreate();
        if (!queue->heap) {
            SAFE_FREE(queue);
            return NULL;
        }

        queue->heap->greater = comp;
    }

    return queue;
}

void priorityQueueRelease(PriorityQueue *queue)
{
    if(queue != NULL) {
        minHeapRelease(queue->heap);
        queue->heap = NULL;

        SAFE_FREE(queue);
    }
}

int priorityQueuePush(PriorityQueue *queue, ElemType val)
{
    return_val_if_fail(queue != NULL && queue->heap != NULL, ERROR);

    return minHeapPush(queue->heap, val);
}

int priorityQueuePop(PriorityQueue *queue, ElemType *val)
{
    return_val_if_fail(queue != NULL && queue->heap != NULL, ERROR);

    return minHeapPop(queue->heap, val);
}

unsigned int priorityQueueSize(PriorityQueue *queue)
{
    return_val_if_fail(queue != NULL && queue->heap != NULL, ERROR);

    return minHeapSize(queue->heap);
}

BOOL priorityQueueEmpty(PriorityQueue *queue)
{
    return queue->heap->size == 0u;
}

int priorityQueueTop(PriorityQueue *queue, ElemType *val)
{
    return_val_if_fail(queue != NULL && queue->heap != NULL, ERROR);

    return minHeapTop(queue->heap, val);
}

int priorityQueueBack(PriorityQueue *queue, ElemType *val)
{
    return_val_if_fail(queue != NULL && queue->heap != NULL, ERROR);

    if (queue->heap->size <= 0) {
        return ERROR;
    }

    *val = queue->heap->data[queue->heap->size - 1];

    return OK;

}

