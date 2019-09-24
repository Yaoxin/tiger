/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-18
 */

#include <stdlib.h>
#include "sort.h"

void s_swap(int *const a, int *const b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert_sort(int v[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j > 0 && v[j - 1] > v[j]; j--) {
            s_swap(&v[j - 1], &v[j]);
        }
    }
}

//对较大规模并且无序的数据非常有效，是插入排序的升级版
void shell_sort(int v[], int n)
{
    int gap, i, j;
    //先分组，最开始的增量为数组长度的一半
    for (gap = n / 2; gap > 0; gap /= 2) {
        //对各个分组进行排序
        //对各个组进行插入的时候并不是先对一个组排序完再对另一个组进行排序，而是轮流对每个组进行插入排序
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                s_swap(&v[j], &v[j + gap]);
            }
        }
    }
}

void select_sort(int v[], int n)
{
    int i, j, min_index;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            s_swap(&v[i], &v[min_index]);
        }
    }
}

void merge_sort_array(int v[], int left, int middle, int right, int temp[])
{
    int i = left;
    int m = middle;
    int j = middle + 1;
    int n = right;
    int k = 0;

    while (i <= m && j <= n) {
        if (v[i] <= v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
        }
    }

    while (i <= m) {
        temp[k++] = v[i++];
    }

    while (j <= n) {
        temp[k++] = v[j++];
    }

    int g;
    for (g = 0; g < k; g++) {
        v[left + g] = temp[g];
    }
}

void merge_sort_impl(int v[], int left, int right, int temp[])
{
    if (left < right) {
        int middle = left + ((right - left) >> 1);
        merge_sort_impl(v, left, middle, temp);
        merge_sort_impl(v, middle + 1, right, temp);
        merge_sort_array(v, left, middle, right, temp);
    }
}

//归并排序，需要额外空间，自底向上的递归。
void merge_sort(int v[], int n)
{
    int l = 0, r = n - 1;
    int *temp = (int *) calloc((size_t) n, sizeof(int));
    merge_sort_impl(v, l, r, temp);
}

int quick_sort_partition(int v[], int l, int r)
{
    int k = v[l];
    int i = l, j = r + 1; //左-->右 从第二个元素开始   右-->左 从最后一个元素开始
    do {
        do {
            i++;
        } while (v[i] < k);

        do {
            j--;
        } while (v[j] > k);

        s_swap(&v[i], &v[j]);
    } while (i < j);

    s_swap(&v[i], &v[j]); //撤销最后一次交换
    s_swap(&v[l], &v[j]);

    return j;
}

//以下实现个人觉得比较清晰地描述了快排的思想
void quick_sort_impl(int v[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int s = quick_sort_partition(v, left, right); //s为分裂位置
    quick_sort_impl(v, left, s - 1);
    quick_sort_impl(v, s + 1, right);
}

void quick_sort(int v[], int n)
{
    quick_sort_impl(v, 0, n - 1);
}

void bubble_sort(int v[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                s_swap(&v[j], &v[j + 1]);
            }
        }
    }
}

void heap_sort(int v[], int n)
{

}

