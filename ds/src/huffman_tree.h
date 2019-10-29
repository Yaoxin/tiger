/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

//带权路径长度WPL最小的二叉树称做哈夫曼树
//可以用于数据压缩
//设需要编码的字符集为{d1, d2, d3, ...,dn},各个字符在电文中出现的次数或频率集合为{w1,w2,...,wn},
//以d1,d2,...,dn作为叶子节点，以w1,w2,...,wn作为叶子节点的权值来构造一颗哈夫曼树。规定哈夫曼树的左
//分支为0，右分支为1，则从根节点到叶子节点所经过的路径分支组成的0和1的序列便为该节点对应的字符的编码，
//称为哈夫曼编码。

#ifndef TIGER_HUFFMAN_TREE_H
#define TIGER_HUFFMAN_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#define CODE_LEN    8

typedef struct _huffmanNode
{
  char ch;
  int weight;
  char code[CODE_LEN];
  struct _huffmanNode *left;
  struct _huffmanNode *right;
} HuffmanNode;

typedef HuffmanNode *HuffmanTree;

HuffmanTree huffmanTreeCreate(const char *ch_w);
void huffmanTreeRelease(HuffmanTree tree);

void huffmanEncode(HuffmanTree tree);
void huffmanPrint(HuffmanTree tree);

#ifdef __cplusplus
}
#endif

#endif //TIGER_HUFFMAN_TREE_H
