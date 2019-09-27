/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-09-27
 */

//嵌套锁
//采用了装饰模式，该实现专注于实现嵌套功能，不关心锁的具体实现

#ifndef TIGER_LOCKER_NEST_H
#define TIGER_LOCKER_NEST_H

#include "locker.h"

typedef int (*GetTaskID)(void);

Locker *locker_nest_create(Locker *real_locker, GetTaskID get_task_id);

#endif //TIGER_LOCKER_NEST_H
