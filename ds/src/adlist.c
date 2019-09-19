#include <stdlib.h>
#include "adlist.h"

list *listCreate(void)
{
    struct list *list;

    if ((list = (struct list *) malloc(sizeof(*list))) == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;

    return list;
}

void listRelease(list *list)
{
    unsigned long len;
    listNode *current, *next;

    current = list->head;
    len = list->len;

    while (len--) {
        next = current->next;
        if (list->free) {
            list->free(current->value);
        }

        free(current);

        current = next;
    }

    free(list);
}

list *listAddNodeHead(list *list, void *value)
{
    listNode *node;
    if ((node = (listNode *) malloc(sizeof(*node))) == NULL) {
        return NULL;
    }

    node->value = value;
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->len++;

    return list;
}

list *listAddNodeTail(list *list, void *value)
{
    listNode *node;
    if ((node = (listNode *) malloc(sizeof(*node))) == NULL) {
        return NULL;
    }

    node->value = value;
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }

    list->len++;

    return list;
}

// after = 0 插入到old_node之前
// after = 1 插入到old_node之后
list *listInsertNode(list *list, listNode *old_node, void *value, int after)
{
    listNode *node;
    if ((node = (listNode *) malloc(sizeof(*node))) == NULL) {
        return NULL;
    }

    node->value = value;
    if (after) {
        node->prev = old_node;
        node->next = old_node->next;
        if (list->tail == old_node) {
            list->tail = node;
        }
    } else {
        node->next = old_node;
        node->prev = old_node->prev;
        if (list->head == old_node) {
            list->head = node;
        }
    }

    if (node->prev) {
        node->prev->next = node;
    }

    if (node->next) {
        node->next->prev = node;
    }

    list->len++;

    return list;
}

void listDelNode(list *list, listNode *node)
{
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    if (list->free) {
        list->free(node->value);
    }

    free(node);

    list->len--;
}

// 索引以 0 为起始，也可以是负数， -1 表示链表最后一个节点，诸如此类。
// 如果索引超过范围，返回NULL
listNode *listIndex(list *list, long index)
{
    listNode *node;

    if (index < 0) {
        index = -index - 1;
        node = list->tail;
        while (index-- && node) {
            node = node->prev;
        }
    } else {
        node = list->head;
        while (index-- && node) {
            node = node->next;
        }
    }

    return node;
}

void listRotate(list *list)
{
    listNode *tail = list->tail;
    if (list->len <= 1) {
        return;
    }

    //取出表尾节点
    list->tail = tail->prev;
    list->tail->next = NULL;

    //插入到表头
    list->head->prev = tail;
    tail->next = list->head;
    tail->prev = NULL;
    list->head = tail;
}

listIter *listGetIterator(list *list, int direction)
{
    listIter *iter;

    if ((iter = (listIter *) malloc(sizeof(*iter))) == NULL) {
        return NULL;
    }

    if (direction == AL_START_HEAD) {
        iter->next = list->head;
    } else {
        iter->next = list->tail;
    }
    iter->direction = direction;

    return iter;
}

listNode *listNext(listIter *iter)
{
    listNode *current = iter->next;

    if (current != NULL) {
        if (iter->direction == AL_START_HEAD) {
            iter->next = current->next;
        } else {
            iter->next = current->prev;
        }
    }

    return current;
}

void listReleaseIterator(listIter *iter)
{
    free(iter);
}

list *listDup(list *orig)
{
    list *copy;
    listIter *iter;
    listNode *node;

    if ((copy = listCreate()) == NULL) {
        return NULL;
    }

    copy->dup = orig->dup;
    copy->free = orig->free;
    copy->match = orig->match;

    iter = listGetIterator(orig, AL_START_HEAD);
    if (iter == NULL) {
        return NULL;
    }

    while ((node = listNext(iter)) != NULL) {
        void *value;
        if (orig->dup) {
            value = orig->dup(node->value);
            if (value == NULL) {
                listRelease(copy);
                listReleaseIterator(iter);
                return NULL;
            }
        } else {
            value = listNodeValue(node);
        }

        if (listAddNodeHead(copy, value) == NULL) {
            listRelease(copy);
            listReleaseIterator(iter);
            return NULL;
        }
    }

    listReleaseIterator(iter);

    return copy;
}

listNode *listSearchKey(list *list, void *key)
{
    listIter *iter;
    listNode *node;

    iter = listGetIterator(list, AL_START_HEAD);
    if (iter == NULL)
        return NULL;

    while ((node = listNext(iter)) != NULL) {
        if (list->match) {
            if (list->match(node->value, key)) {
                listReleaseIterator(iter);
                return node;
            }
        } else {
            if (node->value == key) {
                listReleaseIterator(iter);
                return node;
            }
        }
    }

    listReleaseIterator(iter);

    return NULL;
}

// 将迭代器的指针指向表头
void listRewind(list *list, listIter *li)
{
    li->direction = AL_START_HEAD;
    li->next = list->head;

}

// 将迭代器的指针指向表尾
void listRewindTail(list *list, listIter *li)
{
    li->direction = AL_START_TAIL;
    li->next = list->tail;
}