/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

#include <ctype.h>
#include "cstring.h"
#include "darray.h"
#include "queue.h"
#include "huffman_tree.h"

int huffman_bubble_sort(void **array, size_t nr, DataCompareFunc cmp)
{
    size_t i;
    size_t max;
    size_t right;

    return_val_if_fail(array != NULL && cmp != NULL, ERROR);

    if (nr < 2) {
        return OK;
    }

    for (right = nr - 1; right > 0; right--) {
        for (i = 1, max = 0; i < right; i++) {
            if (cmp(array[i], array[max]) > 0) {
                max = i;
            }
        }

        if (cmp(array[max], array[right]) > 0) {
            void *data = array[right];
            array[right] = array[max];
            array[max] = data;
        }
    }

    return OK;
}

//升序比较
int cmp_huffman_node(void *ctx, void *data)
{
    HuffmanNode *a = (HuffmanNode *) ctx;
    HuffmanNode *b = (HuffmanNode *) data;
    return a->weight < b->weight;
}

void _getcode(char *str, char *ch, int *weight)
{
    if (str == NULL) {
        return;
    }

    while (isspace(*str)) {
        str++;
    }

    if (!isalpha(*str)) {
        return;
    }

    *ch = *str;
    str++;
    *weight = 0;
    while (isdigit(*str)) {
        *weight += 10 * *weight + (*str - '0');
        str++;
    }
}

//输入要正确，没有做太多异常检测
DArray *_init_huffman_code(const char *ch_w)
{
    DArray *array = darrayCreate(NULL, NULL);
    char *input = string_dup(ch_w);
    char *recv[26] = {};
    int num = 0;
    string_split(input, ";", recv, &num);

    char ch = '0';
    int weight;
    int i;
    for (i = 0; i < num; i++) {
        _getcode(recv[i], &ch, &weight);
        printf("%c %d\n", ch, weight);
        if (ch != '0') {
            HuffmanNode *node = (HuffmanNode *) calloc(1, sizeof(HuffmanNode));
            node->ch = ch;
            node->weight = weight;
            node->left = node->right = NULL;
            darrayAppend(array, (void *) node);
        }
    }

    SAFE_FREE(input);

    return array;
}

//根据提供的字符串列表构造哈夫曼树
HuffmanTree huffmanTreeCreate(const char *ch_w)
{
    HuffmanTree root = NULL;
    DArray *array = _init_huffman_code(ch_w);

    while (darrayLength(array) > 0) {
        darraySort(array, huffman_bubble_sort, cmp_huffman_node);
        if (darrayLength(array) == 1) {
            darrayIndex(array, 0, (void *) &root);
            darrayDelete(array, 0);
        } else {
            HuffmanNode *first, *second;
            darrayIndex(array, 0, (void *) &first);
            darrayIndex(array, 1, (void *) &second);
            darrayDelete(array, 0);
            darrayDelete(array, 0);

            HuffmanNode *node = (HuffmanNode *) calloc(1, sizeof(HuffmanNode));
            node->weight = first->weight + second->weight;
            if (cmp_huffman_node(first, second)) {
                node->left = first;
                node->right = second;
            } else {
                node->left = second;
                node->right = first;
            }
            darrayAppend(array, (void *)node);
        }
    }

    darrayRelease(array);

    return root;
}

void huffmanTreeRelease(HuffmanTree tree)
{
    if (tree != NULL) {
        huffmanTreeRelease(tree->left);
        huffmanTreeRelease(tree->right);
        SAFE_FREE(tree);
    }
}

//实现哈夫曼编码, 采用层序遍历方式
void huffmanEncode(HuffmanTree tree)
{
    Queue *queue = queueCreate(NULL, NULL);
    HuffmanNode *cur = tree;

    if (cur) {
        enqueue(queue, (void *) cur);
    }

    while (!queueEmpty(queue)) {
        dequeue(queue, (void *) &cur);
        if (cur->left) {
            enqueue(queue, (void *) cur->left);
            string_copy(cur->left->code, cur->code);
            char *p = cur->left->code;
            while (*p != '\0') {
                p++;
            }
            *p = '0';
        }

        if (cur->right) {
            enqueue(queue, (void *) cur->right);
            string_copy(cur->left->code, cur->code);
            char *p = cur->left->code;
            while (*p != '\0') {
                p++;
            }
            *p = '1';
        }
    }

    queueRelease(queue);
}

void huffmanPrint(HuffmanTree tree)
{
    if (tree != NULL) {
        huffmanPrint(tree->left);
        if (tree->left == NULL && tree->right == NULL) {
            printf("%c\t%s\n", tree->ch, tree->code);
        }
        huffmanPrint(tree->right);
    }
}
