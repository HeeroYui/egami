/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_WRAPPER_SVG_H__
#define __EGAMI_WRAPPER_SVG_H__

#include <egami/egami.h>

namespace egami
{
	bool LoadSVG(const etk::UString& _fileName, egami::Image& _ouputImage, const ivec2& _size=ivec2(-1,-1));
};

#endif