/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

#include <assert.h>
#include "rw_locker.h"

typedef enum _RWLockerMode
{
  RW_LOCKER_NONE,
  RW_LOCKER_WR,
  RW_LOCKER_RD,
  RW_LOCKER_NR
} RWLockerMode;

struct _RWLocker
{
  int readers;
  RWLockerMode mode;
  Locker *wr_locker;
  Locker *rd_locker;
};

RWLocker *rw_locker_create(Locker *wr_locker, Locker *rd_locker)
{
    return_val_if_fail(wr_locker != NULL && rd_locker != NULL, NULL);
    RWLocker *rw_locker = (RWLocker *) calloc(1, sizeof(RWLocker));
    if (rw_locker != NULL) {
        rw_locker->readers = 0;
        rw_locker->mode = RW_LOCKER_NONE;
        rw_locker->wr_locker = wr_locker;
        rw_locker->rd_locker = rd_locker;
    }

    return rw_locker;
}

int rw_locker_wrlock(RWLocker *rw_locker)
{
    int ret = OK;
    return_val_if_fail(rw_locker != NULL, ERROR);

    if ((ret = locker_lock(rw_locker->wr_locker)) == OK) {
        rw_locker->mode = RW_LOCKER_WR;
    }

    return ret;
}
int rw_locker_rdlock(RWLocker *rw_locker)
{
    int ret = OK;
    return_val_if_fail(rw_locker != NULL, ERROR);

    if ((ret = locker_lock(rw_locker->rd_locker)) == OK) {
        rw_locker->readers++;
        if (rw_locker->readers == 1) {
            ret = locker_lock(rw_locker->wr_locker);
            rw_locker->mode = RW_LOCKER_RD;
        }
        locker_unlock(rw_locker->rd_locker);
    }

    return ret;
}
int rw_locker_unlock(RWLocker *rw_locker)
{
    int ret = OK;
    return_val_if_fail(rw_locker != NULL, ERROR);

    assert(rw_locker->mode == RW_LOCKER_WR || rw_locker->mode == RW_LOCKER_RD);

    if (rw_locker->mode == RW_LOCKER_WR) {
        rw_locker->mode = RW_LOCKER_NONE;
        ret = locker_unlock(rw_locker->wr_locker);
    } else {
        if ((ret = locker_lock(rw_locker->rd_locker)) == OK) {
            rw_locker->readers--;
            if (rw_locker->readers == 0) {
                ret = locker_unlock(rw_locker->wr_locker);
                rw_locker->mode = RW_LOCKER_NONE;
            }
            locker_unlock(rw_locker->rd_locker);
        }
    }

    return ret;
}

void rw_locker_destroy(RWLocker *rw_locker)
{
    if (rw_locker != NULL) {
        locker_destroy(rw_locker->rd_locker);
        locker_destroy(rw_locker->wr_locker);

        SAFE_FREE(rw_locker);
    }
}