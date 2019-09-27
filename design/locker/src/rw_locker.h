/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

//读写锁

#ifndef TIGER_RW_LOCKER_H
#define TIGER_RW_LOCKER_H

#include "locker.h"

struct _RWLocker;
typedef struct _RWLocker RWLocker;

RWLocker *rw_locker_create(Locker *rw_locker, Locker *rd_locker);

int rw_locker_wrlock(RWLocker *rw_locker);
int rw_locker_rdlock(RWLocker *rw_locker);
int rw_locker_unlock(RWLocker *rw_locker);

void rw_locker_destroy(RWLocker *rw_locker);

#endif //TIGER_RW_LOCKER_H
