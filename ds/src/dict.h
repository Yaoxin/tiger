/*
 * @Description:
 * @Author: cloudy
 * @Date: 2019-09-18
 */

//模仿redis dict结构实现

#include "stdint.h"

#ifndef TIGER_DICT_H
#define TIGER_DICT_H

#define DICT_OK 0
#define DICT_ERR 1

/*data struct*/
typedef struct dictEntry
{
    void *key;

    union {
        void *val;
        u_int64_t u64;
        int64_t s64;
    } v;

    struct dictEntry *next;
} dictEntry;

typedef struct dictType
{
    unsigned int (*hashFunction)(const void *key);
    void *(*keyDup)(void *privdata, const void *key);
    void *(*valDup)(void *privdata, const void *obj);
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);

    void (*keyDestructor)(void *privdata, void *key);
    void (*valDestructor)(void *privdata, void *obj);

} dictType;

typedef struct dictht
{

    // 哈希表数组
    dictEntry **table;

    unsigned long size;
    unsigned long sizemask;

    unsigned long used;

} dictht;

typedef struct dict
{
    dictType *type;
    void *privdata;

    dictht ht[2];

    int rehashidx;
    int iterators;

} dict;

/*Macros*/
#define dictFreeVal(d, entry) \
    if ((d)->type->valDestructor) \
        (d)->type->valDestructor((d)->privdata, (entry)->v.val)


#define dictSetVal(d, entry, _val_) do { \
    if((d)->type->valDup) \
        entry->v.val = (d)->type->valDup((d)->privdata, _val_); \
    else \
        entry->v.val = (_val_);\
} while(0)

#define dictSetSignedIntegerVal(entry, _val_) \
    do { entry->v.s64 = _val_; } while(0)

#define dictSetUnsignedIntegerVal(entry, _val_) \
    do { entry->v.u64 = _val_; } while(0)


#define dictFreeKey(d, entry) \
    if((d)->type->keyDestructor) \
        (d)->type->keyDestructor((d)->privdata, (entry)->key)

#define dictSetKey(d, entry, _key_) do { \
    if ((d)->type->keyDup) \
        entry->key = (d)->type->keyDup((d)->privdata, _key_); \
    else \
        entry->key = (_key_);\
} while (0)

//比较两个键
#define dictCompareKeys(d, key1, key2) \
    (((d)->type->keyCompare) ? (d)->type->keyCompare((d)->privdata, key1, key2) : (key1) == (key2))

#define dictHashKey(d, key) (d)->type->hashFunction(key)
#define dictGetKey(he) ((he)->key)
#define dictGetVal(he) ((he)->v.val)
#define dictGetSignedIntegerVal(he) ((he)->v.s64)
#define dictGetUnsignedIntegerVal(he) ((he)->v.u64)
#define dictSlots(d) ((d)->ht[0].size + (d)->ht[1].size)
#define dictSize(d) ((d)->ht[0].used + (d)->ht[1].used)
#define dictIsRehashing(ht) ((ht)->rehashidx != -1)



/*API*/
dict *dictCreate(dictType *type, void *privDataPtr);
int dictExpand(dict *d, unsigned long size);
int dictAdd(dict *d, void *key, void *val);
dictEntry *dictAddRaw(dict *d, void *key);
int dictReplace(dict *d, void *key, void *val);
dictEntry *dictReplaceRaw(dict *d, void *key);
int dictDelete(dict *d, const void *key);
int dictDeleteNoFree(dict *d, const void *key);
void dictRelease(dict *d);
dictEntry *dictFind(dict *d, const void *key);
void *dictFetchValue(dict *d, const void *key);
int dictRehash(dict *d, int n);

#endif
