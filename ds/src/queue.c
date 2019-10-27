/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-18
 */

#include <stdlib.h>
#include "queue.h"

Queue *queueCreate(DataDestroyFunc data_destroy, void *ctx)
{
    Queue *queue = calloc(1, sizeof(Queue));
    if (queue != NULL) {
        queue->data_destroy = data_destroy;
        queue->data_destory_ctx = ctx;
        queue->front = queue->rear = 0;
    }
}

void queueRelease(Queue *queue)
{
    if (queue != NULL) {
        while (queue->front != (queue->rear + 1) % MAXSIZE) {
            if (queue->data_destroy != NULL) {
                queue->data_destroy(queue->data_destory_ctx, queue->data[queue->front]);
            }

            queue->front = (queue->front + 1) % MAXSIZE;
        }

        SAFE_FREE(queue);
    }
}

int enqueue(Queue *queue, void *val)
{
    return_val_if_fail(queue != NULL , ERROR);
    if ((queue->rear + 1) % MAXSIZE == queue->front) {
        //队列满
        return ERROR;
    }

    queue->data[queue->rear] = val;
    queue->rear = (queue->rear + 1) % MAXSIZE;

    return OK;
}

int dequeue(Queue *queue, void **val)
{
    return_val_if_fail(queue != NULL, ERROR);
    if (queue->front == queue->rear) {
        //队列空
        return ERROR;
    }

    *val = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;

    return OK;
}

size_t queueLength(Queue *queue)
{
    return (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

BOOL queueEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}
