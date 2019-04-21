/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-21
 */

#include "yx_log.h"
#include "yx_file.h"

int main(int argc, char *argv[]) {
    log_set_level(T_LOG_DEBUG);
    log_set_log_prefix("../log/test");

    int r = yx_dir_create("../ffd/");
    YX_DEBUG("return code: %d", r);

    return 0;
}