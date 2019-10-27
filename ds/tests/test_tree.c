/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-27
 */

#include <stdio.h>
#include "tree.h"
#include "trie.h"

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

void test_trie_tree()
{
    TrieTree tree = trieTreeCreate();
    insertString(tree, "hello");
    insertString(tree, "helag");
    insertString(tree, "aonondag");
    BOOL found = searchString(tree, "hello");
    printf("first found %d\n", found);
    deleteString(tree, "hello");
    found = searchString(tree, "hello");
    printf("second found %d\n", found);
    found = searchString(tree, "aonondag");
    printf("three found %d\n", found);
}

int main(int argc, char *argv[])
{
//    test_tree();
    test_trie_tree();
    return 0;
}

