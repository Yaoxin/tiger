/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-20
 */

#include "yx_file.h"

int yx_file_size(const char *filename)
{
    struct stat stat_info;

    int r = stat(filename, &stat_info);
    if (r < 0) return -1;

    return (int) stat_info.st_size;

}

int yx_file_size_by_fd(int fd)
{
    struct stat stat_info;

    int r = fstat(fd, &stat_info);
    if (r < 0) return -1;

    return (int) stat_info.st_size;
}

int yx_file_exist(const char *filename)
{
    struct stat stat_info;

    if (stat(filename, &stat_info) == 0) {
        if (S_ISDIR(stat_info.st_mode)) return -1;
        return 1;
    }

    return 0;
}

int yx_dir_exist(const char *dirname)
{
    struct stat stat_info;

    if (lstat(dirname, &stat_info) == 0) {
        if (S_ISDIR(stat_info.st_mode)) return 1;
        else return -1;
    }

    return 0;
}

int yx_dir_create(const char *dirname)
{
    char dname[512];
    char *lc = NULL;
    unsigned long name_len = 0;
    unsigned long pos = 0;
    while (1) {
        lc = strchr(dirname + pos, '/');
        if (NULL == lc) break;
        name_len = lc - dirname;
        pos += name_len + 1;
        strncpy(dname, dirname, name_len);
        dname[name_len] = '\0';

        int r = yx_dir_exist(dname);
        if (r == -1) return -1;
        else if (r == 1) continue;
        else {
            mode_t mask = umask(0);
            if (mkdir(dname, (mode_t) 0700 | mask) == -1) {
                umask(mask);
                return -1;
            }

            umask(mask);
        }
    }

    return 0;
}