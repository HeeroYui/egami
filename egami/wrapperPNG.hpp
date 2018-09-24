/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <egami/egami.hpp>

namespace egami {
	/**
	 * @breif Load a png file in the image.
	 * @param[in] _uri Uri of the file.
	 * @return Read Image.
	 */
	egami::Image loadPNG(const etk::Uri& _uri);
	/**
	 * @breif Load a png file in the image.
	 * @param[in] _buffer File buffer.
	 * @return Read Image.
	 */
	egami::Image loadPNG(const etk::Vector<uint8_t>& _buffer);
	/**
	 * @breif Store a PNG file in the image.
	 * @param[in] _uri Uri of the file.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storePNG(const etk::Uri& _uri, const egami::Image& _inputImage);
	/**
	 * @breif Store a PNG file in the image.
	 * @param[out] _buffer output file buffer.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storePNG(etk::Vector<uint8_t>& _buffer, const egami::Image& _inputImage);
}

