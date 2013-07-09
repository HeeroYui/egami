/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_DEBUG_H__
#define __EGAMI_DEBUG_H__

#include <etk/types.h>
#include <etk/Debug.h>

extern const char * egamiLibName;

#define EGAMI_CRITICAL(data)    ETK_CRITICAL(egamiLibName, data)
#define EGAMI_WARNING(data)     ETK_WARNING(egamiLibName, data)
#define EGAMI_ERROR(data)       ETK_ERROR(egamiLibName, data)
#define EGAMI_INFO(data)        ETK_INFO(egamiLibName, data)
#define EGAMI_DEBUG(data)       ETK_DEBUG(egamiLibName, data)
#define EGAMI_VERBOSE(data)     ETK_VERBOSE(egamiLibName, data)
#define EGAMI_ASSERT(cond,data) ETK_ASSERT(egamiLibName, cond, data)
#define EGAMI_CHECK_INOUT(cond) ETK_CHECK_INOUT(egamiLibName, cond)
#define EGAMI_TODO(cond)        ETK_TODO(egamiLibName, cond)

#endif

