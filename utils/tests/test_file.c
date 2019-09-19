/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "yx_log.h"
#include "yx_file.h"
#include "typedef.h"

int main(int argc, char *argv[])
{
    log_set_level(T_LOG_DEBUG);

    char *ptr = NULL;
    YX_MALLOC(ptr, 512, char *);
    YX_ASSERT_RET(ptr != NULL, -1);
    YX_FREE(ptr);

    YX_ASSERT_RET(ptr == NULL, -1);

    return 0;
}
