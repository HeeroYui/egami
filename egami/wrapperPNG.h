/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_WRAPPER_PNG_H__
#define __EGAMI_WRAPPER_PNG_H__

#include <egami/egami.h>

namespace egami
{
	bool LoadPNG(const etk::UString& _fileName, egami::Image& _ouputImage);
};

#endif

