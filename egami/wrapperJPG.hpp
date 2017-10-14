/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <egami/egami.hpp>

namespace egami {
	/**
	 * @breif Load a jpeg file in the image.
	 * @param[in] _fileName Name of the file.
	 * @return Read Image.
	 */
	egami::Image loadJPG(const etk::String& _fileName);
	/**
	 * @breif Load a jpeg file in the image.
	 * @param[in] _buffer file Buffer
	 * @return Read Image.
	 */
	egami::Image loadJPG(const etk::Vector<uint8_t>& _buffer);
	/**
	 * @breif Store a jpg file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storeJPG(const etk::String& _fileName, const egami::Image& _inputImage);
	/**
	 * @breif Store a jpg file in the image.
	 * @param[out] _buffer output file buffer.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storeJPG(etk::Vector<uint8_t>& _buffer, const egami::Image& _inputImage);
}

