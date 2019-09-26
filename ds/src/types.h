/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-26
 */

#ifndef TIGER_TYPES_H
#define TIGER_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE            0
#endif

#ifndef OK
#define OK 0
#endif

#ifndef ERROR
#define ERROR -1
#endif

typedef void (*DataDestroyFunc)(void *ctx, void *data);
typedef int (*DataCompareFunc)(void *ctx, void *data);
typedef int (*DataVisitFunc)(void *ctx, void *data);

#define return_if_fail(p) if(!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n", \
        __func__, __LINE__); return;}

#define return_val_if_fail(p, ret) if(!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n",\
    __func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}

#ifdef __cplusplus
}
#endif

#endif //TIGER_TYPES_H
