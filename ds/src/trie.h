/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

//字典树实现
//利用字符串检索、存储，以及词频统计
//比较耗内存

#ifndef TIGER_TRIE_H
#define TIGER_TRIE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CHAR_NUM    26

enum NODE_TYPE
{
  TYPE_COMPLETED = 0,
  TYPE_UNCOMPLETED
};

typedef struct _TrieNode
{
  enum NODE_TYPE type;
  char ch;
  int count;
  struct _TrieNode *child[MAX_CHAR_NUM];
} TrieNode;

typedef TrieNode *TrieTree;

TrieTree trieTreeCreate();
void trieTreeRelease(TrieTree tree);

void insertString(TrieTree tree, const char *s);
BOOL searchString(TrieTree tree, const char *s);
BOOL deleteString(TrieTree tree, const char *s);

#ifdef __cplusplus
}
#endif

#endif //TIGER_TRIE_H
