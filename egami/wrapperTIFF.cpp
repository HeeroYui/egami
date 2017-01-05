/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperTIFF.hpp>
#include <etk/os/FSNode.hpp>


egami::Image egami::loadTIFF(const std::string& _inputFile) {
	egami::Image out;
	etk::FSNode fileName(_inputFile);
	if (fileName.exist() == false) {
		EGAMI_ERROR("File does not existed='" << fileName << "'");
		return out;
	}
	if(fileName.fileOpenRead() == false) {
		EGAMI_ERROR("Can not find the file name='" << fileName << "'");
		return out;
	}
	
	
	
	
	
	
	return out;
}

