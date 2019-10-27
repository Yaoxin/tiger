/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

#include <stdio.h>
#include "tree.h"

int print_int(void *ctx, void *data)
{
    printf("%d ", (int) data);
    return 0;
}

int sum_int(void *ctx, void *data)
{
    *(int *) ctx += (int) data;
}

void test_tree()
{
    //long的长度和void *相同
    long a[] = {1, 0, 2, 3};
    BitTree tree = treeCreate((void *) a, 4, NULL, NULL);
    preorder(tree, print_int, NULL);
    printf("\n");
    preorder_norec(tree, print_int, NULL);
    printf("\n");
    inorder(tree, print_int, NULL);
    printf("\n");
    inorder_norec(tree, print_int, NULL);
    printf("\n");
    postorder(tree, print_int, NULL);
    printf("\n");
    postorder_norec(tree, print_int, NULL);
    printf("\n");
    levelorder(tree, print_int, NULL);
    printf("\n");
    treeRelease(tree);
}

int main(int argc, char *argv[])
{
    test_tree();
    return 0;
}

