/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-24
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.h"

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp > BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = (char) c;
    }
}

int get_word(char *word, int lim)
{
    char *w = word;
    int c;

    while (isspace(c = getch()));

    if (c != EOF) {
        *w++ = (char)c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        *w = (char)getch();
        if (!isalnum(*w)) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';

    return word[0];
}

int get_int(int *pn)
{
    int c, sign;
    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = (char) c;
    }

    if (c == '\n') {
        s[i] = (char) c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

int string_compare(const char *s, const char *t)
{
    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }

    return *s - *t;
}

char *string_copy(char to[], const char from[])
{
    int i = 0;
    char *ret = to;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }

    return ret;
}

char *string_dup(const char *s) {
    char *p = (char *)calloc(1, strlen(s) + 1);
    if (p != NULL) {
        string_copy(p, s);
    }

    return p;
}

int string_reverse(char *s)
{
    char *p1 = s;
    char *p2 = s + (strlen(s) - 1);

    while (p1 < p2) {
        char c = *p1;
        *p1 = *p2;
        *p2 = c;
        p1++;
        p2--;
    }

    return 0;

}

//1. 如果有前导空白字符，则跳过
//2. 如果有符号位，则读取符号位
//3. 取整数部分
int atoi_m(const char s[])
{
    int i, sign;
    int n = 0;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    for (; isdigit(s[i]); i++) {
        n = 10 * n + (s[i] - '0');
    }

    return sign * n;
}

double atof_m(const char s[])
{
    int i, sign;
    double n, power;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    for (n = 0.0; isdigit(s[i]); i++) {
        n = 10.0 * n + (s[i] - '0');
    }

    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        n = 10.0 * n + (s[i] - '0');
        power *= 10;
    }

    return sign * n / power;
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) {
        n = -n;
    }

    i = 0;
    do {
        s[i++] = '0' + (n % 10);

    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    string_reverse(s);
}

int htoi(const char s[])
{
    int n = 0;
    int i = 0;

    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
        i += 2;
    }

    while (s[i] != '\0') {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            n = 16 * n + (c - '0');
        } else if (c >= 'a' && c <= 'f') {
            n = 16 * n + 10 + (c - 'a');
        } else if (c >= 'A' && c <= 'F') {
            n = 16 * n + 10 + (c - 'A');
        } else {
            //所有不合格的十六进制字符串，都返回-1
            return -1;
        }

        ++i;
    }

    return n;
}

//空格符、制表符、换行符
int string_trim(char s[])
{
    size_t i;
    for (i = strlen(s) - 1; i >= 0; i--) {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
            break;
        }
    }
    s[++i] = '\0';

    return (int) i;
}