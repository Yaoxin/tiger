/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-18
 */

#include "sort.h"

void insert_sort(int v[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j > 0 && v[j - 1] > v[j]; j--) {
            temp = v[j - 1];
            v[j - 1] = v[j];
            v[j] = temp;
        }
    }

}

void shell_sort(int v[], int n)
{

}

void select_sort(int v[], int n)
{
    int i, j, tmp, min_index;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            tmp = v[i];
            v[i] = v[min_index];
            v[min_index] = tmp;
        }
    }
}

void merge_sort(int v[], int n)
{

}

void quick_sort_impl(int v[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int i = left, j = right, key = v[i];
    while (i < j) {
        
    }
}

void quick_sort(int v[], int n)
{

}

void bubble_sort(int v[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void heap_sort(int v[], int n)
{

}

