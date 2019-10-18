/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-18
 */

//关于子串的算法总结

#include <stdio.h>
#include <string.h>
#include "substring.h"

//子串匹配 暴力法
//也称为朴素模式匹配算法
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

//已知next [0, ..., j]，如何求出next [j + 1]呢？
//对于P的前j+1个序列字符：
//若p[k] == p[j]，则next[j + 1 ] = next [j] + 1 = k + 1；
//若p[k ] ≠ p[j]，如果此时p[ next[k] ] == p[j ]，则next[ j + 1 ] =  next[k] + 1，
//否则继续递归前缀索引k = next[k]，而后重复此过程。 
//相当于在字符p[j+1]之前不存在长度为k+1的前缀"p0 p1, …, pk-1 pk"跟后缀“pj-k pj-k+1, …, pj-1 pj"相等，
//那么是否可能存在另一个值t+1 < k+1，使得长度更小的前缀 “p0 p1, …, pt-1 pt”
//等于长度更小的后缀 “pj-t pj-t+1, …, pj-1 pj” 呢？如果存在，那么这个t+1 便是next[ j+1]的值，
//此相当于利用已经求得的next 数组（next [0, ..., k, ..., j]）进行P串前缀跟P串后缀的匹配。
//尝试分析下『dcddcgdcddcd』就会明白为什么要k = next[k]。本质上对称性
size_t get_next(const char *p, int next[])
{
    size_t p_len = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;

    while (j < p_len - 1) {
        //p[k]表示前缀, p[j]表示后缀
        if (k == -1 || p[j] == p[k]) {
            ++k;
            ++j;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

//KMP模式匹配
//核心是要获取next数组，next数组代表当前字符之前的字符串中，
//有多大长度的相同前缀后缀。例如如果next [j] = k，
//代表j之前的字符串中有最大长度为k的相同前缀后缀。
int kmp_string_match(const char *s, const char *p)
{
    int i = 0, j = 0;
    int s_len = strlen(s), p_len = strlen(p);
    int next[256] = {0};
    get_next(p, next);

    while (i < s_len && j < p_len) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j == p_len) {
        return i - j;
    } else {
        return -1;
    }
}
