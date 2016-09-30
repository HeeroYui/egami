/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <egami/egami.hpp>

namespace egami {
	/**
	 * @breif Load a bmp file in the image.
	 * @param[in] _fileName Name of the file.
	 * @return Generate image or empty image
	 */
	egami::Image loadBMP(const std::string& _fileName);
	/**
	 * @breif Store a bmp file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storeBMP(const std::string& _fileName, const egami::Image& _inputImage);
}

