/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-26
 */

//动态数组，对应C++里面的vector

#ifndef TIGER_DARRAY_H
#define TIGER_DARRAY_H

#include <stdio.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DArray
{

  unsigned long size;
  unsigned long alloc_size;
  void **data;

  void * data_destory_ctx;
  DataDestroyFunc data_destory;
} DArray;

#define darrayLength(da) ((da)->size)

DArray *darrayCreate(DataDestroyFunc data_destroy, void *ctx);
void darrayRelease(DArray *thiz);
int darrayInsert(DArray *thiz, size_t index, void *data);
int darrayPrepend(DArray *thiz, void *data);
int darrayAppend(DArray *thiz, void *data);
int darrayDelete(DArray *thiz, size_t index);
int darrayIndex(DArray *thiz, size_t index, void **data);
int darraySetIndex(DArray *thiz, size_t index, void *data);
size_t darraySearchKey(DArray *thiz, DataCompareFunc cmp, void *ctx);
int darrayForeach(DArray *thiz, DataVisitFunc visit, void *ctx);
int darraySort(DArray *thiz, SortFunc sort, DataCompareFunc cmp);

#ifdef __cplusplus
}
#endif

#endif //TIGER_DARRAY_H
