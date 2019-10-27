/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-18
 */

//循环队列实现
//浪费一个空间，代表队列满状态

#ifndef TIGER_QUEUE_H
#define TIGER_QUEUE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXSIZE    512

typedef struct _Queue
{
  void *data[MAXSIZE];
  size_t front;
  size_t rear;

  void * data_destory_ctx;
  DataDestroyFunc data_destroy;
} Queue;

Queue *queueCreate(DataDestroyFunc data_destroy, void *ctx);
void queueRelease(Queue *queue);
int enqueue(Queue *queue, void *val);
int dequeue(Queue *queue, void **val);
size_t queueLength(Queue *queue);
BOOL queueEmpty(Queue *queue);

#ifdef __cplusplus
}
#endif

#endif //TIGER_QUEUE_H
