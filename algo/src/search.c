/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

//顺序查找
int sequential_search(int v[], int n, int k)
{
    int i = 0;
    while (i < n && v[i] != k) {
        i++;
    }

    if (i < n) {
        return i;
    }

    return -1;

}

//折半查找
int binary_search(int v[], int n, int k)
{
    int l = 0, r = n - 1;
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        if (k == v[m]) {
            return m;
        } else if (k < v[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return -1;
}

int interpolat_search(int v[], int n, int k)
{
    int l = 0, r = n - 1;
    int m;
    while (l <= r) {
        m = l + (r - l) * (k - v[l]) / (v[r] - v[l]);
        if (k == v[m]) {
            return m;
        } else if (k < v[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return -1;
}

//斐波那契查找
// v需要预留足够空间吖
//将索引定为1开始更好处理
//核心思路 F(g) -1 = F(g -1) -1 + F(g-2) - 1 + 1(mid所占的一个位置)
int fibonacci_search(int v[], int n, int k)
{
    int f[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    int low = 0, high = n - 1;

    int g = 0;
    while (n > f[g] - 1) {
        g++;
    }

    int i;
    for (i = n; i < f[g] - 1; i++) {
        v[i] = v[n - 1];
    }

    int mid;
    while (low <= high) {
        mid = low + f[g - 1] - 1 + 1;
        if (k > v[mid]) {
            low = mid + 1;
            g = g - 2;
        } else if (k < v[mid]) {
            high = mid - 1;
            g = g - 1;
        } else {
            if (mid <= (n - 1)) {
                return mid;
            } else {
                return n - 1;
            }
        }
    }

    return -1;
}

//子串匹配 暴力法
int brute_force_string_match(const char *str1, const char *str2)
{
    size_t n = strlen(str1), m = strlen(str2);
    int i, j;
    for (i = 0; i <= n - m; i++) {
        j = 0;
        while (j < m && *(str1 + i + j) == *(str2 + j)) {
            j++;
            if (j == m) {
                return i;
            }
        }
    }

    return -1;

}
