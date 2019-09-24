/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-24
 */

#ifndef TIGER_STRING_H
#define TIGER_STRING_H

int getch(void);
void ungetch(int);
int get_word(char *word, int lim);
int get_line(char s[], int lim);
int get_int(int *pn);
int string_compare(const char *s, const char *t);
char *string_copy(char to[], const char from[]);
char *string_dup(const char *s);
int string_reverse(char *s);
int string_trim(char s[]);
int atoi_m(const char s[]);
double atof_m(const char s[]);
void itoa(int n, char s[]);
int htoi(const char s[]);

#endif //TIGER_STRING_H
