/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-30
 */

#include <stdlib.h>
#include "stack.h"

Stack *stackCreate(DataDestroyFunc data_destroy, void *ctx)
{
    Stack *stack = calloc(1, sizeof(Stack));
    if (stack != NULL) {
        stack->sp = 0;
        stack->data_destroy = data_destroy;
        stack->data_destory_ctx = ctx;
    }

    return stack;
}
void stackRelease(Stack *stack)
{
    if (stack != NULL) {
        int i = 0;
        for (i = 0; i < stack->sp; i++) {
            if (stack->data_destroy != NULL) {
                stack->data_destroy(stack->data_destory_ctx, stack->data[i]);
            }
        }

        SAFE_FREE(stack);
    }
}

int stackTop(Stack *stack, void **val)
{
    return_val_if_fail(stack != NULL && stack->sp > 0, ERROR);
    *val = stack->data[stack->sp - 1];

    return OK;
}
int stackPush(Stack *stack, void *val)
{
    return_val_if_fail(stack != NULL && stack->sp < MAXSIZE, ERROR);
    stack->data[stack->sp++] = val;
}

int stackPop(Stack *stack)
{
    return_val_if_fail(stack != NULL && stack->sp > 0, ERROR);

    void *val = stack->data[--stack->sp];
    if (stack->data_destroy) {
        stack->data_destroy(stack->data_destory_ctx, val);
    }

    return OK;
}

size_t stackLength(Stack *stack)
{
    return_val_if_fail(stack != NULL, ERROR);

    return stack->sp;
}

