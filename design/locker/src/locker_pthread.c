/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

#include <stdlib.h>
#include <pthread.h>
#include "locker_pthread.h"

typedef struct _PrivInfo
{
  pthread_mutex_t mutex;
} PrivInfo;

static int locker_pthread_lock(Locker *locker)
{
    PrivInfo *priv = (PrivInfo *) locker->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

    return ret == 0 ? OK : ERROR;
}

static int locker_pthread_unlock(Locker *locker)
{
    PrivInfo *priv = (PrivInfo *) locker->priv;

    int ret = pthread_mutex_unlock(&priv->mutex);

    return ret == 0 ? OK : ERROR;
}

static void locker_pthread_destroy(Locker *locker)
{
    PrivInfo *priv = (PrivInfo *) locker->priv;

    pthread_mutex_destroy(&priv->mutex);

    SAFE_FREE(locker);
}

Locker *locker_pthread_create(void)
{
    Locker *locker = (Locker *) calloc(1, sizeof(Locker) + sizeof(PrivInfo));
    if (locker != NULL) {
        PrivInfo *priv = (PrivInfo *) locker->priv;

        locker->lock = locker_pthread_lock;
        locker->unlock = locker_pthread_unlock;
        locker->destroy = locker_pthread_destroy;

        pthread_mutex_init(&priv->mutex, NULL);
    }
}

