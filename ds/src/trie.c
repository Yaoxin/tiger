/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

#include <string.h>
#include <stdlib.h>
#include "trie.h"

TrieNode *_createNode(char ch)
{
    int i = 0;
    TrieNode *n = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (n) {
        n->count = 1;
        n->type = TYPE_UNCOMPLETED;
        n->ch = ch;
        for (i = 0; i < MAX_CHAR_NUM; i++) {
            n->child[i] = NULL;
        }
    }

    return n;
}

void _deleteNode(TrieNode *node)
{
    if (node == NULL) {
        return;
    }
    int i;
    for (i = 0; i < MAX_CHAR_NUM; i++) {
        _deleteNode(node->child[i]);
    }
    SAFE_FREE(node);
}

int _index(char ch)
{
    return ch - 'a';
}

TrieTree trieTreeCreate()
{
    return _createNode(' ');
}

TrieTree trieTreeRelease(TrieTree tree)
{
    _deleteNode(tree);
}

void insertString(TrieTree tree, const char *s)
{
    int i = 0, len = (int) strlen(s);
    TrieNode *cur = tree;
    for (i = 0; i < len; i++) {
        if (cur->child[_index(s[i])] == NULL) {
            cur->child[_index(s[i])] = _createNode(s[i]);
        } else {
            cur->child[_index(s[i])]->count++;
        }
        cur = cur->child[_index(s[i])];
    }
    cur->type = TYPE_COMPLETED;
}

BOOL searchString(TrieTree tree, const char *s)
{
    int i = 0, len = (int) strlen(s);
    TrieNode *cur = tree;
    for (i = 0; i < len; i++) {
        if (cur->child[_index(s[i])] == NULL) {
            break;
        }
        cur = cur->child[_index(s[i])];
    }

    return i == len && cur->type == TYPE_COMPLETED;
}

BOOL deleteString(TrieTree tree, const char *s)
{
    if (searchString(tree, s) == FALSE) {
        return FALSE;
    }

    int i = 0, len = (int) strlen(s);
    TrieNode *cur = tree;
    for (i = 0; i < len; i++) {
        if (cur->child[_index(s[i])]->count == 1) {
            _deleteNode(cur->child[_index(s[i])]);
        } else {
            cur->child[_index(s[i])]->count--;
        }
        cur = cur->child[_index(s[i])];
    }

}
