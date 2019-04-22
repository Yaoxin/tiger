/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-20
 */


#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "typedef.h"

#ifndef TIGER_YX_FILE_H
#define TIGER_YX_FILE_H

DECLS_BEGIN

int yx_file_size(const char *filename);

int yx_file_size_by_fd(int fd);

int yx_file_exist(const char *filename);

int yx_dir_exist(const char *dirname);

int yx_dir_create(const char *dirname);

DECLS_END

#endif //TIGER_YX_FILE_H
