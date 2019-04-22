/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-21
 */

//实现简单的堆和优先级队列，以及基于堆的排序

#include "typedef.h"

#ifndef TIGER_HEAP_H
#define TIGER_HEAP_H

DECLS_BEGIN

typedef void *ElemType;

typedef struct min_heap {
    ElemType *data;
    unsigned int n, a;
} min_heap_t;

static inline int min_heap_elem_greater(ElemType a, ElemType b);

static inline int min_heap_empty(min_heap_t *s);

static inline unsigned int min_heap_size(min_heap_t *s);

static inline ElemType min_heap_top(min_heap_t *s);

static inline int min_heap_reserve(min_heap_t *s, unsigned int n);

static inline int min_heap_push(min_heap_t *s, ElemType e);

static inline ElemType min_heap_pop(min_heap_t *s);

static inline int min_heap_erase(min_heap_t *s, ElemType e);

static inline void min_heap_shift_up_(min_heap_t *s, unsigned hole_index, ElemType e);

static inline void min_heap_shift_down_(min_heap_t *s, unsigned hole_index, ElemType e);

int min_heap_empty(min_heap_t *s) { return 0u == s->n; }


DECLS_END
#endif //TIGER_HEAP_H
