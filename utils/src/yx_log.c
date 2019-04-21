/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-20
 */

// 多线程安全版本

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "yx_log.h"
#include "yx_file.h"

#define LOG_FILE_MAX_SIZE   (50 * 1024 * 1024)

int use_file = 0;
int log_level = T_LOG_INFO;
char log_prefix[512] = "../logs/log";
FILE *log_fp = NULL;

static void _log_helper(int level, char *file, char *fun, int line, int log_errno, const char *fmt, va_list ap);

void log_set_level(int level) {
    log_level = level;
}

int log_set_log_prefix(const char *prefix) {
    char dirname[512];
    char *rc = strrchr(prefix, '/');
    if (NULL == rc) {
        fprintf(stderr, "log prefix(%s) is invalid.", prefix);
        return -1;
    }

    strncpy(dirname, prefix, rc - prefix + 1);
    dirname[rc - prefix + 1] = '\0';

    int r = yx_dir_exist(dirname);
    if (r == -1) {
        fprintf(stderr, "dir(%s) anomalous.", dirname);
        return -1;
    } else if (r == 0) {
        if (yx_dir_create(dirname) == -1) {
            fprintf(stderr, "create dir(%s) failed.", dirname);
            return -1;
        }
    }

    use_file = 1;
    snprintf(log_prefix, sizeof(log_prefix) - 1, "%s", prefix);

    return 0;
}

static char *get_log_time(char *tm_str, unsigned int tm_size) {
    time_t ms = time(NULL);
    struct tm *tm_obj = localtime(&ms);

    snprintf(tm_str, tm_size, "%d-%02d-%02d %02d:%02d:%02d", tm_obj->tm_year + 1900, tm_obj->tm_mon + 1,
             tm_obj->tm_mday, tm_obj->tm_hour, tm_obj->tm_min, tm_obj->tm_sec);

    return tm_str;
}

static char *get_log_level(int level, char *msg, unsigned int msg_size) {
    if (level == T_LOG_TRACE) {
        snprintf(msg, msg_size, "TRACE");
    } else if (level == T_LOG_DEBUG) {
        snprintf(msg, msg_size, "DEBUG");
    } else if (level == T_LOG_INFO) {
        snprintf(msg, msg_size, "INFO");
    } else if (level == T_LOG_ERR) {
        snprintf(msg, msg_size, "ERR");
    } else {
        snprintf(msg, msg_size, "UNKNOWN");
    }

    return msg;
}

static int is_need_reopen_logfile() {
    if (log_fp == NULL) return 1;

    int filesize = yx_file_size_by_fd(fileno(log_fp));
    if (filesize < 0) {
        fprintf(stderr, "%s::%s(%d) err: %s", __FILE__, __FUNCTION__, __LINE__, strerror(errno));
        return -1;
    }

    if (filesize < LOG_FILE_MAX_SIZE) return 0;

    return 1;
}

static int open_logfile() {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);

    int r = is_need_reopen_logfile();
    if (r < 0) return r;

    char new_filename[512];
    char filename[512];
    if (log_fp != NULL) {
        snprintf(filename, sizeof(filename) - 1, "%s_%d.log", log_prefix, 0);
        snprintf(new_filename, sizeof(new_filename) - 1, "%s_%d.log", log_prefix, 1);
        rename(filename, new_filename);
        fclose(log_fp);
    } else {
        snprintf(filename, sizeof(filename) - 1, "%s_%d.log", log_prefix, 0);
    }

    log_fp = fopen(filename, "a+");
    if (log_fp == NULL) {
        fprintf(stderr, "fopen(%s) err(%s)", filename, strerror(errno));
        return -1;
    }

    dup2(fileno(log_fp), STDOUT_FILENO);
    dup2(fileno(log_fp), STDERR_FILENO);

    pthread_mutex_unlock(&mutex);

    return 0;
}

static void log_file_output(const char *msg) {
    if (NULL == msg) return;

    int r = open_logfile();
    if (r < 0) {
        fprintf(stderr, "open log file ERR!!!\n");
        return;
    }

    fprintf(log_fp, "%s\n", msg);
    fflush(log_fp);
}

void log_output(int level, int log_errno, char *file, char *fun, int line, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    _log_helper(level, file, fun, line, log_errno, fmt, ap);
    va_end(ap);
}

static void _log_helper(int level, char *file, char *fun, int line, int log_errno, const char *fmt, va_list ap) {
    char tmstr[32];
    char level_str[16];
    char buf[1024];
    size_t len;

    int idx = snprintf(buf, sizeof(buf) - 1, "[%d][%s][%s]%s::%s(%d):",
                       getpid(), get_log_time(tmstr, sizeof(tmstr) - 1),
                       get_log_level(level, level_str, sizeof(level_str) - 1),
                       file, fun, line);
    if (idx < 0) return;

    if (fmt != NULL)
        vsnprintf(buf + idx, sizeof(buf) - idx - 1, fmt, ap);
    else
        buf[0] = '\0';

    if (log_errno >= 0) {
        len = strlen(buf);
        if (len < sizeof(buf) - 3) {
            snprintf(buf + len, sizeof(buf) - len, ": %s",
                     strerror(log_errno));
        }
    }

    if (use_file == 1) {
        log_file_output(buf);
    } else {
        fprintf(stderr, "%s\n", buf);
    }
}


