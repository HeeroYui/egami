/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_WRAPPER_EDF_H__
#define __EGAMI_WRAPPER_EDF_H__

#include <egami/egami.h>

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
	 * @param[out] _ouputImage Read data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool loadEDF(const std::string& _fileName, egami::Image& _ouputImage);
	/**
	 * @breif Store a edf file in the image.
	 * @param[in] _fileName Name of the file.
	 * @param[in] _inputImage write data.
	 * @return true if all is done correctly, false otherwise.
	 */
	bool storeEDF(const std::string& _fileName, const egami::Image& _inputImage);
};

#endif

