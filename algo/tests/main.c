/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

#include <stdio.h>
#include "sort.h"
#include "search.h"
#include "permutation.h"
#include "substring.h"

typedef void (*func)(int *, int);

void print_vector(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void test_sort()
{
    int i;
    func sort_fun_map[] = {
        bubble_sort,
        insert_sort,
        select_sort,
        quick_sort,
        merge_sort,
        shell_sort,
    };

    int sort_fun_len = sizeof(sort_fun_map) / sizeof(sort_fun_map[0]);

    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    for (i = 0; i < sort_fun_len; ++i) {
        sort_fun_map[i](arr, arr_len);
        print_vector(arr, arr_len);
    }

    int arr1[] = {8, 0};
    arr_len = sizeof(arr1) / sizeof(arr1[0]);
    for (i = 0; i < sort_fun_len; ++i) {
        sort_fun_map[i](arr1, arr_len);
        print_vector(arr1, arr_len);
    }

    int arr2[] = {18, 10, 0, 79, 4, 67, 9};
    arr_len = sizeof(arr2) / sizeof(arr2[0]);
    for (i = 0; i < sort_fun_len; ++i) {
        sort_fun_map[i](arr2, arr_len);
        print_vector(arr2, arr_len);
    }
}

void test_string_match()
{
    int idx = brute_force_string_match("NOBODY_NOTICED_HIM", "NOT");
    printf("find index: %d\n", idx);

    int idy = kmp_string_match("NOBODY_NOTICED_HIM", "NOT");
    printf("find index: %d\n", idy);

}

void test_permutation()
{
    lookup_permutation(5);
    printf("----------------------------\n");
    lexi_order_permutation(5);
    printf("----------------------------\n");
    johnson_trotter(5);
}

void test_search()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int idx = interpolat_search(v, sizeof(v) / sizeof(v[0]), 5);
    printf("use interpolat_search, find index: %d\n", idx);

    int v1[100] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int idx2 = fibonacci_search(v, 9, 8);
    printf("use fibonacci_search, find index: %d\n", idx2);

}

int main(int argc, char *argv[])
{
    test_sort();
    test_string_match();
    test_permutation();
    test_search();
    return 0;
}

