/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-10-18
 */

#ifndef TIGER_SUBSTRING_H
#define TIGER_SUBSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

int brute_force_string_match(const char *str1, const char * str2);
int kmp_string_match(const char *s, const char *p);

#ifdef __cplusplus
}
#endif

#endif //TIGER_SUBSTRING_H
