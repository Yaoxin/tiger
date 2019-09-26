/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-26
 */

#include "types.h"
#include <stdlib.h>
#include "darray.h"

static void darrayDestoryData(DArray *thiz, void *data)
{
    if (thiz->data_destory != NULL) {
        thiz->data_destory(thiz->data_destory_ctx, data);
    }
}

DArray *darrayCreate(DataDestroyFunc data_destroy, void *ctx)
{
    DArray *thiz = (DArray*) calloc(1, sizeof(DArray));
    if (thiz != NULL) {
        thiz->data = NULL;
        thiz->size = 0;
        thiz->alloc_size = 0;
        thiz->data_destory_ctx = ctx;
        thiz->data_destory = data_destroy;
    }

    return thiz;
}

void darrayRelease(DArray *thiz)
{
    size_t i = 0;

    if (thiz != NULL) {
        for (i = 0; i < thiz->size; i++) {
            darrayDestoryData(thiz, thiz->data[i]);
        }

        SAFE_FREE(thiz->data);
        SAFE_FREE(thiz);
    }
}

#define MIN_PRE_ALLOCATE_NR 10
static int darrayExpand(DArray *thiz, unsigned long need)
{
    return_val_if_fail(thiz != NULL, ERROR);

    if ((thiz->size + need) > thiz->alloc_size) {
        unsigned long alloc_size = thiz->alloc_size + (thiz->alloc_size >> 1) + MIN_PRE_ALLOCATE_NR;

        void **data = (void **) realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL) {
            thiz->data = data;
            thiz->alloc_size = alloc_size;
        }
    }

    return ((thiz->size + need) <= thiz->alloc_size) ? OK : ERROR;
}

static int darrayShrink(DArray *thiz)
{
    return_val_if_fail(thiz != NULL, ERROR);

    if ((thiz->size < (thiz->alloc_size >> 1)) && (thiz->alloc_size > MIN_PRE_ALLOCATE_NR)) {
        size_t alloc_size = thiz->size + (thiz->size >> 1);

        void **data = (void **) realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL) {
            thiz->data = data;
            thiz->alloc_size = alloc_size;
        }
    }

    return OK;
}

int darrayInsert(DArray *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL, ERROR);

    int ret = ERROR;
    size_t cursor = index;
    cursor = cursor < thiz->size ? cursor : thiz->size;

    if (darrayExpand(thiz, 1) == OK) {
        size_t i = 0;
        for (i = thiz->size; i > cursor; i--) {
            thiz->data[i] = thiz->data[i - 1];
        }

        thiz->data[cursor] = data;
        thiz->size++;

        ret = OK;
    }

    return ret;
}

int darrayPrepend(DArray *thiz, void *data)
{
    return darrayInsert(thiz, 0, data);
}
int darrayAppend(DArray *thiz, void *data)
{
    return darrayInsert(thiz, darrayLength(thiz), data);
}
int darrayDelete(DArray *thiz, size_t index)
{
    return_val_if_fail(thiz != NULL && thiz->size > index, ERROR);

    darrayDestoryData(thiz, thiz->data[index]);

    size_t i = 0;
    for (i = index; (i + 1) < thiz->size; i++) {
        thiz->data[i] = thiz->data[i + 1];
    }
    thiz->size--;

    darrayShrink(thiz);

    return OK;
}
int darrayIndex(DArray *thiz, size_t index, void **data)
{
    return_val_if_fail(thiz != NULL && data != NULL && index < thiz->size,
                       ERROR);

    *data = thiz->data[index];

    return OK;

}
int darraySetIndex(DArray *thiz, size_t index, void *data)
{
    return_val_if_fail(thiz != NULL && index < thiz->size,
                       ERROR);

    thiz->data[index] = data;

    return OK;
}
size_t darraySearchKey(DArray *thiz, DataCompareFunc cmp, void *ctx)
{
    size_t i = 0;

    return_val_if_fail(thiz != NULL && cmp != NULL, ERROR);

    for (i = 0; i < thiz->size; i++) {
        if (cmp(ctx, thiz->data[i]) == 0) {
            break;
        }
    }

    return i;
}
int darrayForeach(DArray *thiz, DataVisitFunc visit, void *ctx)
{
    size_t i = 0;
    int ret = OK;
    return_val_if_fail(thiz != NULL && visit != NULL, ERROR);

    for (i = 0; i < thiz->size; i++) {
        ret = visit(ctx, thiz->data[i]);
    }

    return ret;
}

