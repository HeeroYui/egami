/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <egami/debug.h>

int32_t egami::getLogId() {
	static int32_t g_val = elog::registerInstance("egami");
	return g_val;
}
