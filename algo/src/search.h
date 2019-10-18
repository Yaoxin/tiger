/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

//常用的查找算法总结

#ifndef TIGER_SEARCH_H
#define TIGER_SEARCH_H

#ifdef __cplusplus
extern "C" {
#endif

int sequential_search(int v[], int n, int k);
int binary_search(int v[], int n, int k);
int interpolat_search(int v[], int n, int k);
int fibonacci_search(int v[], int n, int k);

#ifdef __cplusplus
}
#endif

#endif //TIGER_SEARCH_H
