/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-26
 */

#include "tree.h"
#include "queue.h"
#include "stack.h"

//注意考虑空节点定义, NULL == (void *)0
BitTree treeCreate(void *data[], unsigned data_len, DataDestroyFunc data_destroy, void *data_destroy_ctx)
{
    TreeNode *root = (TreeNode *) calloc(1, sizeof(TreeNode));
    return_val_if_fail(root != NULL, NULL);
    root->data = *data;
    root->left = root->right = NULL;
    Queue *queue = queueCreate(NULL, NULL);
    enqueue(queue, (void *) root);

    int idx = 0, ret = OK;
    TreeNode *temp = NULL, *cur = NULL;
    while (!queueEmpty(queue) && idx < data_len) {
        if (dequeue(queue, (void *) &cur) == ERROR) {
            break;
        }

        if (idx++ && idx < data_len && *(data + idx) != NULL) {
            temp = (TreeNode *) calloc(1, sizeof(TreeNode));
            temp->data = *(data + idx);
            temp->left = temp->right = NULL;
            cur->left = temp;
            enqueue(queue, (void *) temp);
        }

        if (idx++ && idx < data_len && *(data + idx) != NULL) {
            temp = (TreeNode *) calloc(1, sizeof(TreeNode));
            temp->data = *(data + idx);
            temp->left = temp->right = NULL;
            cur->right = temp;
            enqueue(queue, (void *) temp);
        }
    }

    queueRelease(queue);
    return root;
}

//递归后序删除
void treeRelease(BitTree tree)
{
    if (tree == NULL) {
        return;
    }

    treeRelease(tree->left);
    treeRelease(tree->right);

    if (tree->data_destroy != NULL) {
        tree->data_destroy(tree->data_destroy_ctx, tree->data);
    }
    SAFE_FREE(tree);
}

//前序遍历操作
void preorder(BitTree tree, DataVisitFunc fun, void *ctx)
{
    if (tree == NULL) {
        return;
    }
    fun(ctx, tree->data);
    preorder(tree->left, fun, ctx);
    preorder(tree->right, fun, ctx);
}

//中序遍历操作
void inorder(BitTree tree, DataVisitFunc fun, void *ctx)
{
    if (tree == NULL) {
        return;
    }
    inorder(tree->left, fun, ctx);
    fun(ctx, tree->data);
    inorder(tree->right, fun, ctx);
}

//后序遍历操作
void postorder(BitTree tree, DataVisitFunc fun, void *ctx)
{
    if (tree == NULL) {
        return;
    }
    postorder(tree->left, fun, ctx);
    postorder(tree->right, fun, ctx);
    fun(ctx, tree->data);
}

//前序非递归遍历
void preorder_norec(BitTree tree, DataVisitFunc fun, void *ctx)
{
    Stack *stack = stackCreate(NULL, NULL);
    TreeNode *cur = tree;

    if (cur) {
        stackPush(stack, (void *) cur);
    }

    while (!stackEmpty(stack)) {
        stackTop(stack, (void *) &cur);
        stackPop(stack);

        fun(ctx, cur->data);
        if (cur->right) {
            stackPush(stack, (void *) cur->right);
        }

        if (cur->left) {
            stackPush(stack, (void *) cur->left);
        }
    }
    stackRelease(stack);
}

//中序非递归遍历
void inorder_norec(BitTree tree, DataVisitFunc fun, void *ctx)
{
    Stack *stack = stackCreate(NULL, NULL);
    TreeNode *cur = tree;

    while (cur || !stackEmpty(stack)) {
        while (cur) {
            stackPush(stack, (void *) cur);
            cur = cur->left;
        }

        if (!stackEmpty(stack)) {
            stackTop(stack, (void *) &cur);
            fun(ctx, cur->data);
            stackPop(stack);
            cur = cur->right;
        }
    }
//    哈哈，这种方法需要记录节点是否被访问过，需要在节点增加一个状态字段
//    if (cur) {
//        stackPush(stack, (void *) cur);
//    }
//
//    while (!stackEmpty(stack)) {
//        stackTop(stack, (void *) &cur);
//        if (cur->left) {
//            stackPush(stack, (void *) cur->left);
//        } else {
//            stackPop(stack);
//            fun(ctx, cur->data);
//            if (cur->right) {
//                stackPush(stack, (void *) cur->right);
//            }
//        }
//    }

    stackRelease(stack);
}

//后序非递归遍历
void postorder_norec(BitTree tree, DataVisitFunc fun, void *ctx)
{
    Stack *stack = stackCreate(NULL, NULL);
    TreeNode *cur = tree;
    TreeNode *pre = NULL;

    if (cur) {
        stackPush(stack, (void *) cur);
    }

    while (!stackEmpty(stack)) {
        stackTop(stack, (void *) &cur);
        if ((cur->left == NULL && cur->right == NULL) || (pre && (pre == cur->left || pre == cur->right))) {
            fun(ctx, cur->data);
            stackPop(stack);
            pre = cur;
        } else {
            if (cur->right) {
                stackPush(stack, (void *) cur->right);
            }

            if (cur->left) {
                stackPush(stack, (void *) cur->left);
            }
        }
    }

    stackRelease(stack);
}

//层次遍历
void levelorder(BitTree tree, DataVisitFunc fun, void *ctx)
{
    Queue *queue = queueCreate(NULL, NULL);
    TreeNode *cur = tree;

    if (cur) {
        enqueue(queue, (void *) cur);
    }

    while (!queueEmpty(queue)) {
        dequeue(queue, (void *) &cur);
        fun(ctx, cur->data);

        if (cur->left) {
            enqueue(queue, (void *) cur->left);
        }

        if (cur->right) {
            enqueue(queue, (void *) cur->right);
        }
    }

    queueRelease(queue);
}

