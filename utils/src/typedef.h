/*
 * @Description: 
 * @Author: cloudy
 * @Date: 2019-04-22
 */

#ifndef TIGER_TYPEDEF_H
#define TIGER_TYPEDEF_H

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "yx_log.h"

#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif

#define YX_ASSERT(p) if(!(p)) \
    {YX_ERR(" "#p" ERR"); return;}

#define YX_ASSERT_RET(p, ret) if(!(p)) \
    {YX_ERR(" "#p" ERR"); return (ret);}

#define YX_ASSERT_ERR(p, ret) if(!(p)) \
    {YX_SYS_ERR(errno, " "#p" ERR"); return (ret);}

#define YX_MALLOC(p, size, type) \
do {\
    p = (type)malloc(size);  \
	if(p == NULL) { \
		YX_ERR("malloc(%d) ERR(%s)", size, strerror(errno));  \
	} else { \
		memset(p, 0, size); \
	} \
} while(0)

#define YX_FREE(p) if(p != NULL) {free(p); p = NULL;}


#endif //TIGER_TYPEDEF_H
