/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-20
 */


#ifndef TIGER_YX_LOG_H
#define TIGER_YX_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum LogLevel {
    T_LOG_TRACE = 0,
    T_LOG_DEBUG = 1,
    T_LOG_INFO = 2,
    T_LOG_ERR = 3
} LogLevel;

#ifdef LOG_TRACE
#define LOG_LEVEL   T_LOG_TRACE
#endif

#ifdef LOG_DEBUG
#define LOG_LEVEL   T_LOG_DEBUG
#endif

#ifdef LOG_INFO
#define LOG_LEVEL   T_LOG_INFO
#endif

#ifdef LOG_ERR
#define LOG_LEVEL   T_LOG_ERR
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL   T_LOG_INFO
#endif

extern int log_level;

void log_set_level(int level);

int log_set_log_prefix(const char *prefix);

void log_output(int level, int log_errno, char *file, char *fun, int line, char *fmt, ...);

#define YX_LOG(level, log_errno, fmt, ...) \
do {                            \
    if(level >= log_level)    \
        log_output(level, log_errno, (char *)__FILE__, (char *)__FUNCTION__, __LINE__, (char *)fmt, ## __VA_ARGS__); \
} while(0)

#define YX_INFO(fmt, ...)        YX_LOG(T_LOG_INFO, -1,        fmt, ## __VA_ARGS__)
#define YX_ERR(fmt, ...)        YX_LOG(T_LOG_ERR, -1,        fmt, ## __VA_ARGS__)
#define YX_SYS_ERR(log_errno, fmt, ...)    YG_LOG(T_LOG_ERR, log_errno,        fmt, ## __VA_ARGS__)


#ifndef NO_DEBUG
#define YX_TRACE(fmt, ...)    YX_LOG(T_LOG_TRACE, -1,    fmt, ## __VA_ARGS__)
#define YX_DEBUG(fmt, ...)    YX_LOG(T_LOG_DEBUG, -1,    fmt, ## __VA_ARGS__)
#else
#define YX_TRACE(fmt, ...) do {;} while (0)
#define YX_DEBUG(fmt, ...) do {;} while (0)
#endif

#ifdef __cplusplus
}
#endif
#endif //TIGER_YX_LOG_H
