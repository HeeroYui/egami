/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Vector.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/Color.hpp>
#include <egami/Image.hpp>
#include <egami/ImageMono.hpp>
#include <etk/uri/Uri.hpp>

namespace egami {
	/**
	 * @brief Load a specific ilage file in the requested image data.
	 * @param[in] _uri Uri of the file (SVG, BMP, PNG).
	 * @param[in] _size Dimention of the file when resizable (SVG).
	 */
	egami::Image load(const etk::Uri& _uri, const ivec2& _size=ivec2(-1,-1) );
	/**
	 * @brief Load a specific ilage file in the requested image data.
	 * @param[in] _mineType mineType of the buffer.
	 * @param[in] _buffer memory file.
	 * @param[in] _size Dimention of the file when resizable (SVG).
	 */
	egami::Image load(const etk::String& _mineType, const etk::Vector<uint8_t>& _buffer, const ivec2& _size=ivec2(-1,-1) );
	/**
	 * @brief Save an image in a file.
	 * @param[in] _input Data of the image.
	 * @param[in] _uri Uri of the file.
	 * @return true if the file is corectly Stored, false otherwise
	 */
	bool store(const egami::Image& _input, const etk::Uri& _uri);
	/**
	 * @brief Save an image in a memory buffer.
	 * @param[in] _input Data of the image.
	 * @param[out] _buffer Store file in this buffer.
	 * @param[in] _mineType mineType of the output buffer.
	 * @return true if the file is corectly Stored, false otherwise
	 */
	bool store(const egami::Image& _input, etk::Vector<uint8_t>& _buffer, const etk::String& _mineType);
	/**
	 * @brief know if a file can have multiple size definition.
	 * @param[in] _uri Uri of the file.
	 * @return true if the format is scalable.
	 */
	bool scalable(const etk::Uri& _uri);
	/**
	 * @brief Generate a distance field output file from an input file;
	 * @param[in] _input Input file name
	 * @param[in] _output Output file name
	 * @return true All done corectly.
	 * @return false An error occured.
	 */
	bool generateDistanceFieldFile(const etk::Uri& _input, const etk::Uri& _output);
}


