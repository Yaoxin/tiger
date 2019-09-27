/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

//locker的协议

#ifndef TIGER_LOCKER_H
#define TIGER_LOCKER_H

#include "types.h"


#ifdef __cplusplus
extern "C" {
#endif

struct _Locker;
typedef struct _Locker Locker;

typedef int (*LockerLockFunc)(Locker *locker);
typedef int (*LockerUnlockFunc)(Locker *locker);
typedef void (*LockerDestroyFunc)(Locker *locker);

struct _Locker
{
  LockerLockFunc lock;
  LockerUnlockFunc unlock;
  LockerDestroyFunc destroy;

  char priv[0];
};

static inline int locker_lock(Locker *locker)
{
    return_val_if_fail(locker != NULL && locker->lock != NULL, ERROR);

    return locker->lock(locker);
}

static inline int locker_unlock(Locker *locker)
{
    return_val_if_fail(locker != NULL && locker->unlock != NULL, ERROR);

    return locker->unlock(locker);
}

static inline void locker_destroy(Locker *locker)
{
    return_if_fail(locker != NULL && locker->destroy != NULL);

    locker->destroy(locker);
}

#ifdef __cplusplus
}
#endif

#endif //TIGER_LOCKER_H
