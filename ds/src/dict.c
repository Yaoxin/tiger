#include "stdlib.h"
#include "dict.h"

int a = 3;

static void _dictReset(dictht *ht)
{
    ht->table = NULL;
    ht->size = 0;
    ht->sizemask = 0;
    ht->used = 0;
}

static int _dictInit(dict *d, dictType *type, void *privDataPtr)
{
    _dictReset(&d->ht[0]);
    _dictReset(&d->ht[1]);

    d->type = type;
    d->privdata = privDataPtr;
    d->rehashidx = -1;
    d->iterators = 0;

    return DICT_OK;
}

dict *dictCreate(dictType *type, void *privDataPtr)
{
    dict *d = (dict *)malloc(sizeof(*d));

    _dictInit(d, type, privDataPtr);

    return d;
}

int dictExpand(dict *d, unsigned long size)
{
}

int dictAdd(dict *d, void *key, void *val)
{
    dictEntry *entry = dictAddRaw(d, key);
    if (!entry)
        return DICT_ERR;

    dictSetVal(d, entry, val);

    return DICT_OK;
}

static void _dictRehashStep(dict *d)
{
    if(d->iterators == 0)
        dictRehash(d, 1);
}

dictEntry *dictAddRaw(dict *d, void *key)
{
    if (dictIsRehashing(d))
        _dictRehashStep(d);
}

int dictReplace(dict *d, void *key, void *val)
{
}

dictEntry *dictReplaceRaw(dict *d, void *key)
{
}

int dictDelete(dict *d, const void *key)
{
}

int dictDeleteNoFree(dict *d, const void *key)
{
}

void dictRelease(dict *d)
{
}

dictEntry *dictFind(dict *d, const void *key)
{
}

void *dictFetchValue(dict *d, const void *key)
{
}

//执行n步渐进式rehash
int dictRehash(dict *d, int n)
{
    

}
