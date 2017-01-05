/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <egami/egami.hpp>

namespace egami {
	/**
	 * @breif Load a bmp file in the image.
	 * A simple example of EDF file is :
	 * [PRE]
	 * #EDF //Example Of EDF file (5,5)
	 *   *  
	 *  * * 
	 * *   *
	 *  * * 
	 *   *  
	 * [PRE]
	 * @param[in] _fileName Name of the file.
	 * @return Read Image
	 */
	egami::Image loadEDF(const std::string& _fileName);
	/**
	 * @breif Store a edf file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storeEDF(const std::string& _fileName, const egami::Image& _inputImage);
}

