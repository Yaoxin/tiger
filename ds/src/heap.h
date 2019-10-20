/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-21
 */

// 最小堆实现
// 以后做堆设计时需要根据存储的类型适当调整接口

#include "types.h"

#ifndef TIGER_HEAP_H
#define TIGER_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void *ElemType;

typedef struct _minHeap
{
  ElemType *data;
  unsigned int size; //当前大小
  unsigned int capacity; //当前容量

  int (*greater)(ElemType a, ElemType b);
} minHeap;

#define minHeapSetGreaterMethod(h, m)   ((h)->greater = (m))

static inline unsigned int minHeapSize(minHeap *heap);
minHeap *minHeapCreate();
void minHeapRelease(minHeap *heap);
int minHeapTop(minHeap *heap, ElemType *val);
int minHeapPush(minHeap *heap, ElemType val);
int minHeapPop(minHeap *heap, ElemType *val);

unsigned int minHeapSize(minHeap *heap)
{
    return heap->size;
}

#ifdef __cplusplus
}
#endif

#endif //TIGER_HEAP_H
