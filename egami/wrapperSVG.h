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
	/**
	 * @breif Load a svg file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[out] _ouputImage Read data.
	 * @param[in] _size size of the output image.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool loadSVG(const std::string& _fileName, egami::Image& _ouputImage, const ivec2& _size=ivec2(-1,-1));
};

#endif