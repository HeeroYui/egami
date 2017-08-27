/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <egami/egami.hpp>

namespace egami {
	/**
	 * @brief Load a svg file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[in] _size size of the output image.
	 * @return Generated image
	 */
	egami::Image loadSVG(const etk::String& _fileName, const ivec2& _size=ivec2(-1,-1));
}

