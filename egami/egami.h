/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_H__
#define __EGAMI_H__

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>
#include <egami/Image.h>
#include <egami/ImageMono.h>

namespace egami
{
	/**
	 * @brief Load a specific ilage file in the requested image data.
	 * @param[out] _output Data of the image.
	 * @param[in] _fileName Name of the file (SVG, BMP, PNG).
	 * @param[in] _size Dimention of the file when resizable (SVG).
	 * @return true if the file is corectly loaded, false otherwise.
	 */
	bool load(egami::Image& _output, const std::string& _fileName, const ivec2& _size=ivec2(-1,-1) );
	/**
	 * @brief Save an image in a file.
	 * @param[in] _input Data of the image.
	 * @param[in] _fileName Name of the file.
	 * @return true if the file is corectly Stored, false otherwise
	 */
	bool store(const egami::Image& _input, const std::string& _fileName);
	/**
	 * @brief know if a file can have multiple size definition.
	 * @param[in] _fileName Name of the file.
	 * @return true if the format is scalable.
	 */
	bool scalable(const std::string& _fileName);
};

#endif

