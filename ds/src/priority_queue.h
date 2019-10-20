/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-20
 */

// 基于堆实现的优先级队列

#ifndef TIGER_PRIORITY_QUEUE_H
#define TIGER_PRIORITY_QUEUE_H

#include "heap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*ElemComp)(ElemType a, ElemType b);

typedef struct _PriorityQueue
{
  minHeap *heap;
} PriorityQueue;

PriorityQueue *priorityQueueCreate(ElemComp comp);
void priorityQueueRelease(PriorityQueue *queue);
int priorityQueuePush(PriorityQueue *queue, ElemType val);
int priorityQueuePop(PriorityQueue *queue, ElemType *val);
unsigned int priorityQueueSize(PriorityQueue *queue);
BOOL priorityQueueEmpty(PriorityQueue *queue);
int priorityQueueTop(PriorityQueue *queue, ElemType *val);
int priorityQueueBack(PriorityQueue *queue, ElemType *val);

#ifdef __cplusplus
}
#endif

#endif //TIGER_PRIORITY_QUEUE_H
