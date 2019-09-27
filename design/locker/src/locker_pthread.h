/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

#ifndef TIGER_LOCKER_PTHREAD_H
#define TIGER_LOCKER_PTHREAD_H

#include "locker.h"

#ifdef __cplusplus
extern "C" {
#endif

Locker *locker_pthread_create(void);

#ifdef __cplusplus
}
#endif

#endif //TIGER_LOCKER_PTHREAD_H
