/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darray.h"
#include "stack.h"
#include "queue.h"

int total(void *ctx, void *data)
{
    int *sum = (int *) ctx;
    printf("%lu\n", (unsigned long) data);
    *sum += (unsigned long) data;

    return OK;
}

void test_darray()
{
    //64位环境，(void *)占8个字节
    unsigned long i = 0, n = 10;
    DArray *darray = darrayCreate(NULL, NULL);

    for (i = 0; i < n; i++) {
        darrayPrepend(darray, (void *) (2 * i));
        darrayAppend(darray, (void *) i);
    }

    unsigned long sum = 0;
    darrayForeach(darray, total, &sum);
    printf("sum: %lu\n", sum);
    darrayRelease(darray);
}

void test_stack()
{
    int i;
    Stack *stack = stackCreate(NULL, NULL);

    for (i = 0; i < 10; i++) {
        stackPush(stack, (void *) (2 * i));
    }

    size_t len = stackLength(stack);
    for (i = 0; i < len; i++) {
        void *val;
        stackTop(stack, &val);
        printf("%d\n", (int) val);
        stackPop(stack);
    }
}

int get_prioraty(value)
{

    switch (value) {
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        default:return 0;
    }
}

int prioraty(o1, o2)
{
    if (get_prioraty(o1) <= get_prioraty(o2)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void test_stack_2(char *str)
{
    // 未考虑容错
    // 中缀表达式转后缀表达式
    // 9 + (3 - 1*7) * 3 + 10 /2
    //931*-38+10/+

    //5 * 3 + 8 * 9
    //53*89*+
    //5 + 3 * 8 + 9
    //538*+9+

    //1 + (1 + 2 + 3 * 4)
    //112+34*++

    char *ptr = str;
    char c;
    void *val;
    Stack *stack = stackCreate(NULL, NULL);
    Queue *queue = queueCreate(NULL, NULL);
    while (*ptr != '\0') {
        c = *ptr++;
        if (isdigit(c)) {
            enqueue(queue, (void *) c);
        } else if (c == ' ' || c == '\t') {
            continue;
        } else if (c == '(') {
            stackPush(stack, (void *) c);
        } else if (c == ')') {
            while (stackTop(stack, &val) == OK && (char) val != '(') {
                enqueue(queue, val);
                stackPop(stack);
            }
            stackPop(stack);
        } else {
            //当前符号优先级低于栈顶符号
            while (stackTop(stack, &val) == OK && prioraty(c, (char) val) == TRUE) {
                enqueue(queue, val);
                stackPop(stack);
            }
            stackPush(stack, (void *) c);
        }
    }

    while (stackLength(stack) > 0) {
        stackTop(stack, &val);
        if ((char) val != '(' && (char) val != ')') {
            enqueue(queue, val);
            stackPop(stack);
        }
    }

    char out[512] = {0};
    int i = 0;
    while (queueLength(queue) > 0) {
        dequeue(queue, &val);
        out[i++] = (char) val;
    }

    out[i] = '\0';
    printf("%s\n", out);

    stackRelease(stack);
    queueRelease(queue);

}

int main(int argc, char *argv[])
{
    test_darray();
    test_stack();
    test_stack_2("9 + (3 - 1*7) * 3 + 10 /2");

    return 0;
}

