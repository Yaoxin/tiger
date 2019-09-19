/*
 * @Description:
 * @Author: cloudy
 * @Date: 2019-09-18
 */

//双向链表实现
#ifndef TIGER_ADLIST_H
#define TIGER_ADLIST_H

typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;

    void *value;

} listNode;

typedef struct listIter {
    listNode *next;

    int direction;

} listIter;

typedef struct list
{
    listNode *head;
    listNode *tail;

    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);

    unsigned long len;

} list;

#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l, m) ((l)->dup = (m))
#define listSetFreeMethod(l, m) ((l)->free = (m))
#define listSetMatchMethod(l, m) ((l)->match = (m))
#define listGetDupMethod(l) ((l)->dup)
#define listGetFree(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

#define AL_START_HEAD 0
#define AL_START_TAIL 1

list *listCreate(void);
void listRelease(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
void listDelNode(list *list, listNode *node);
listNode *listIndex(list *list, long index);
void listRotate(list *list);

//高级操作
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);

#endif
