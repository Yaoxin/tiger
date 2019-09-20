/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-19
 */

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
