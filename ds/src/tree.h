/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-25
 */

#ifndef TIGER_TREE_H
#define TIGER_TREE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _TreeNode
{
  void *data;
  struct _TreeNode *left;
  struct _TreeNode *right;

  //把这种数据放进node其实挺浪费空间的，这里仅仅是学习演示，真实场景需重新设计
  void * data_destroy_ctx;
  DataDestroyFunc data_destroy;
} TreeNode;

typedef TreeNode *BitTree;

BitTree treeCreate(void *data[], unsigned data_len, DataDestroyFunc data_destroy, void * data_destroy_ctx);
void treeRelease(BitTree tree);

//遍历操作
void preorder(BitTree tree, DataVisitFunc fun, void *ctx);
void inorder(BitTree tree, DataVisitFunc fun, void *ctx);
void postorder(BitTree tree, DataVisitFunc fun, void *ctx);
void preorder_norec(BitTree tree, DataVisitFunc fun, void *ctx);
void inorder_norec(BitTree tree, DataVisitFunc fun, void *ctx);
void postorder_norec(BitTree tree, DataVisitFunc fun, void *ctx);
void levelorder(BitTree tree, DataVisitFunc fun, void *ctx);

#ifdef __cplusplus
}
#endif

#endif //TIGER_TREE_H
