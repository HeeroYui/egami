/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <egami/debug.h>

int32_t egami::getLogId(void) {
	static int32_t g_val = etk::log::registerInstance("egami");
	return g_val;
}
