/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-21
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _PERM_ELEM
{
  int num;
  int dir; //1 左 0 右
} PERM_ELEM;

// C暂时没有实现vector，故打印出来
void print_array(int *arr, int arr_len)
{
    int i;
    for (i = 0; i < arr_len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_perm_array(PERM_ELEM *arr, int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i].num);
    }
    printf("\n");
}

void swap(int *const a, int *const b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(int *arr, int l, int r)
{
    while (l < r) {
        swap(&arr[l], &arr[r]);
        l++;
        r--;
    }
}

int find_max_move_elem_index(PERM_ELEM *arr, int n)
{
    int max_idx = -1;
    int i;
    for (i = 0; i < n; ++i) {
        //向左
        if (arr[i].dir == 1) {
            if (i - 1 >= 0 && arr[i - 1].num < arr[i].num) {
                if (max_idx == -1) {
                    max_idx = i;
                } else if (arr[max_idx].num < arr[i].num) {
                    max_idx = i;
                }
            }
        } else { //向右
            if (i + 1 <= (n - 1) && arr[i].num > arr[i + 1].num) {
                if (max_idx == -1) {
                    max_idx = i;
                } else if (arr[max_idx].num < arr[i].num) {
                    max_idx = i;
                }
            }
        }
    }

    return max_idx;
}

//Steinhaus-Johnson-Trotter算法,满足最小变化的要求，是生成排列的最有效算法之一
void johnson_trotter(int n)
{
    PERM_ELEM *arr = (PERM_ELEM *) calloc((size_t) n, sizeof(PERM_ELEM));
    int i;
    for (i = 0; i < n; i++) {
        arr[i].num = i + 1;
        arr[i].dir = 1;
    }

    print_perm_array(arr, n);
    //1. 找出最大的移动元素k，未找到则终止
    int idx;
    while ((idx = find_max_move_elem_index(arr, n)) != -1) {
        //2. 将最大移动元素和它箭头指向得相邻元素替换
        PERM_ELEM cur = arr[idx];
        if (cur.dir == 1) { //向左
            arr[idx] = arr[idx - 1];
            arr[idx - 1] = cur;
        } else { //向右
            arr[idx] = arr[idx + 1];
            arr[idx + 1] = cur;
        }

        //3. 调转所有大于k的元素的方向
        for (i = 0; i < n; i++) {
            if (arr[i].num > cur.num) {
                arr[i].dir = arr[i].dir == 0 ? 1 : 0;
            }
        }
        print_perm_array(arr, n);
    }
}

void lookup_permutation_impl(int *arr, int l, int r)
{
    if (l == r) {
        print_array(arr, l);
    } else {
        int i;
        for (i = l; i < r; i++) {
            swap(&arr[l], &arr[i]);
            lookup_permutation_impl(arr, l + 1, r);
            swap(&arr[l], &arr[i]);
        }
    }
}

// 回溯递归
void lookup_permutation(int n)
{
    int *arr = (int *) calloc((size_t) n, sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    lookup_permutation_impl(arr, 0, n);
}

int next_permutation(int *arr, int n)
{
    int i;
    for (i = n - 2; i >= 0 && arr[i] > arr[i + 1]; i--);
    if (i < 0) {
        return 0;
    } else {
        int j;
        for (j = n - 1; j > i && arr[i] > arr[j]; j--);
        swap(&arr[j], &arr[i]);
        reverse(arr, i + 1, n - 1);
    }
}

// 字典序获取全排列
void lexi_order_permutation(int n)
{
    int *arr = (int *) calloc((size_t) n, sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    print_array(arr, n);
    while (next_permutation(arr, n)) {
        print_array(arr, n);
    }
}


