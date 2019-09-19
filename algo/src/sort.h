/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-18
 */

//常用排序算法简单总结

#ifndef TIGER_SORT_H
#define TIGER_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

void insert_sort(int v[], int n);

void shell_sort(int v[], int n);

void select_sort(int v[], int n);

void merge_sort(int v[], int n);

void quick_sort(int v[], int n);

void bubble_sort(int v[], int n);

void heap_sort(int v[], int n);


#ifdef __cplusplus
}
#endif

#endif //TIGER_SORT_H
