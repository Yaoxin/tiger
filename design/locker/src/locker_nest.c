/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

#include "locker_nest.h"

typedef struct _PrivInfo
{
  int owner;
  int refcount;
  Locker *real_locker;
  GetTaskID get_task_id;
} PrivInfo;

static int locker_nest_lock(Locker *locker)
{
    int ret = OK;
    PrivInfo *priv = (PrivInfo *) locker->priv;
    if (priv->owner == priv->get_task_id()) {
        priv->refcount++;
    } else {
        if ((ret = locker_lock(priv->real_locker)) == OK) {
            priv->refcount = 1;
            priv->owner = priv->get_task_id();
        }
    }

    return ret;
}

static int locker_nest_unlock(Locker *locker)
{
    int ret = OK;
    PrivInfo *priv = (PrivInfo *) locker->priv;
    return_val_if_fail(priv->owner == priv->get_task_id(), ERROR);

    priv->refcount--;
    if (priv->refcount == 0) {
        priv->owner = 0;
        ret = locker_unlock(priv->real_locker);
    }

    return ret;
}

static void locker_nest_destroy(Locker *locker)
{
    PrivInfo *priv = (PrivInfo *) locker->priv;
    priv->owner = 0;
    priv->refcount = 0;
    locker_destroy(priv->real_locker);
    priv->real_locker = NULL;

    SAFE_FREE(locker);
}

Locker *locker_nest_create(Locker *real_locker, GetTaskID get_task_id)
{
    return_val_if_fail(real_locker != NULL && get_task_id != NULL, NULL);

    Locker *locker = (Locker *) calloc(1, sizeof(Locker) + sizeof(PrivInfo));
    if (locker != NULL) {
        PrivInfo *priv = (PrivInfo *) locker->priv;

        priv->owner = 0;
        priv->refcount = 0;
        priv->real_locker = real_locker;
        priv->get_task_id = get_task_id;
    }
}

