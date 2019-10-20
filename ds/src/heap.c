/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-20
 */

//大多数实现都是给个a[n+1]数组，a[0]置空，heap(1,n)存储在a[1] ~a[n]中，这样满足以下性质：
// root = 1
// value(i) = a[i]
// leftchild(i) = 2 * i
// rightchild(i) = 2 * i + 1
// parent(i) = i / 2

// 这里我们的实现heap(0, n-1) 存储在a[0] ~ a[n-1]中,实现起来也复杂一些
// leftchild(i) = 2 *(i - 1) - 1
// rightchild(i) = 2 * (i -1)
// parent(i) = (i - 1) / 2

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//这种内部的函数入参，可以把控它的正确性，可以不必要做校验
int minHeapReserve(minHeap *heap, unsigned int size)
{
    if (heap->capacity < size) {
        unsigned int capacity = heap->capacity ? heap->capacity * 2 : 8;
        if (capacity < size) {
            capacity = size;
        }

        ElemType *ptr = (ElemType *) realloc(heap->data, capacity * sizeof(ElemType));
        if (!ptr) {
            fprintf(stderr, "Failed realloc heap data.");
            return ERROR;
        }

        heap->data = ptr;
        heap->capacity = capacity;
    }

    return OK;
}

minHeap *minHeapCreate()
{
    minHeap *heap = calloc(1, sizeof(minHeap));
    if (heap != NULL) {
        heap->data = NULL;
        heap->size = heap->capacity = 0;
        heap->greater = NULL;
    }

    return heap;
}

// 该实现未考虑元素delete时的内存释放
void minHeapRelease(minHeap *heap)
{
    if (heap != NULL) {
        if (heap->data) {
            SAFE_FREE(heap->data);
        }

        SAFE_FREE(heap);
    }
}

int minHeapTop(minHeap *heap, ElemType *val)
{
    return_val_if_fail(heap != NULL && heap->size > 0, ERROR);
    *val = *heap->data;
    return OK;
}

void minHeapShiftUp_(minHeap *heap, unsigned int hole_index, ElemType val)
{
    unsigned int parent = hole_index == 0 ? 0 : (hole_index - 1) / 2;
    while (parent && heap->greater(heap->data[parent], val)) {
        heap->data[hole_index] = heap->data[parent];
        hole_index = parent;
        parent = (hole_index - 1) / 2;
    }

    heap->data[hole_index] = val;

}

void minHeapShiftDown_(minHeap *heap, unsigned int hole_index, ElemType val)
{
    unsigned int min_child = 2 * (hole_index - 1);
    while (min_child <= heap->size) {
        // 1. 如果min_child为size,则取a[size-1]。（堆的形状决定的--完全二叉树）
        // 2. 如果min_child <= size -1, 则比较a[min_child-1](左)和a[min_child]（右）,取小的那一个
        min_child -= min_child == heap->size || heap->greater(heap->data[min_child], heap->data[min_child - 1]);

        if (heap->greater(heap->data[min_child], val)) {
            break;
        }

        heap->data[hole_index] = heap->data[min_child];
        hole_index = min_child;
        min_child = 2 * (hole_index - 1);
    }

    //实际上就是heap->data[hole_index] = val啦！
    minHeapShiftUp_(heap, hole_index, val);

}

int minHeapPush(minHeap *heap, ElemType val)
{
    return_val_if_fail(heap != NULL, ERROR);

    if (minHeapReserve(heap, heap->size + 1) != OK) {
        return ERROR;
    }

    minHeapShiftUp_(heap, heap->size++, val);

    return OK;
}

int minHeapPop(minHeap *heap, ElemType *val)
{
    return_val_if_fail(heap != NULL && heap->size > 0, ERROR);

    *val = *heap->data;
    //把最后那个元素放到数组索引0的位置。
    minHeapShiftDown_(heap, 0u, heap->data[--heap->size]);
    return OK;

}




