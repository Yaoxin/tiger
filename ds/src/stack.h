/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-30
 */

#ifndef TIGER_STACK_H
#define TIGER_STACK_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXSIZE    512

typedef struct _Stack
{
  void *data[MAXSIZE];
  unsigned int sp;

  void * data_destory_ctx;
  DataDestroyFunc data_destroy;
} Stack;

Stack *stackCreate(DataDestroyFunc data_destroy, void *ctx);
void stackRelease(Stack *stack);
int stackTop(Stack *stack, void **val);
int stackPush(Stack *stack, void *val);
int stackPop(Stack *stack);
size_t stackLength(Stack *stack);
BOOL stackEmpty(Stack *stack);

#ifdef __cplusplus
}
#endif

#endif //TIGER_STACK_H
