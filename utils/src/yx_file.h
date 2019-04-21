/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-20
 */

#ifndef TIGER_YX_FILE_H
#define TIGER_YX_FILE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

int yx_file_size(const char *filename);

int yx_file_size_by_fd(int fd);

int yx_file_exist(const char *filename);

int yx_dir_exist(const char *dirname);

int yx_dir_create(const char *dirname);

#ifdef __cplusplus
}
#endif
#endif //TIGER_YX_FILE_H
