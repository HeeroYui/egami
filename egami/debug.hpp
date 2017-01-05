/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <elog/log.hpp>

namespace egami {
	int32_t getLogId();
};
#define EGAMI_BASE(info,data) ELOG_BASE(egami::getLogId(),info,data)

#define EGAMI_CRITICAL(data)      EGAMI_BASE(1, data)
#define EGAMI_ERROR(data)         EGAMI_BASE(2, data)
#define EGAMI_WARNING(data)       EGAMI_BASE(3, data)
#ifdef DEBUG
	#define EGAMI_INFO(data)          EGAMI_BASE(4, data)
	#define EGAMI_DEBUG(data)         EGAMI_BASE(5, data)
	#define EGAMI_VERBOSE(data)       EGAMI_BASE(6, data)
	#define EGAMI_TODO(data)          EGAMI_BASE(4, "TODO : " << data)
#else
	#define EGAMI_INFO(data)          do { } while(false)
	#define EGAMI_DEBUG(data)         do { } while(false)
	#define EGAMI_VERBOSE(data)       do { } while(false)
	#define EGAMI_TODO(data)          do { } while(false)
#endif

#define EGAMI_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			EGAMI_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

