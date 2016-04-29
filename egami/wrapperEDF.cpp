/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <egami/debug.h>
#include <egami/Image.h>
#include <egami/wrapperEDF.h>
#include <etk/os/FSNode.h>

//EDF format is a simple format for image in text for distance field image (special case)
// it is composed of the fist line : description of type (starting with #EDF and some other information, the data start just after the first \n

bool egami::loadEDF(const std::string& _inputFile, egami::Image& _ouputImage) {
	
	etk::FSNode file(_inputFile);
	if (false == file.exist()) {
		EGAMI_ERROR("File does not existed='" << file << "'");
		return false;
	}
	if(false == file.fileOpenRead() ) {
		EGAMI_ERROR("Can not find the file name='" << file << "'");
		return false;
	}
	std::string line;
	file.fileGets(line);
	if (etk::start_with(line, "#edf", false) == false) {
		EGAMI_ERROR("This file seams not to be a EDF file ...");
		file.fileClose();
		return false;
	}
	// count number of colomn max an number of line max:
	ivec2 size(0,0);
	while (file.fileGets(line) == true) {
		if (line.size()/2 > (size_t)size.x()) {
			size.setValue(line.size()/2, size.y()+1);
		} else {
			size += ivec2(0,1);
		}
	}
	if (line.size()/2 > (size_t)size.x()) {
		size.setValue(line.size()/2, size.y()+1);
	} else {
		size += ivec2(0,1);
	}
	EGAMI_DEBUG("'" << file << "' ==> size=" << size);
	// jup to the start of the file
	file.fileSeek(0, etk::seekNode_start);
	// drop the first line
	file.fileGets(line);
	
	
	// resize output:
	_ouputImage.resize(size);
	int32_t currentLineId = 0;
	char tmp[3];
	tmp[2] = '\0';
	while (file.fileGets(line) == true) {
		if (line.size() <= 0) {
			continue;
		}
		for (size_t xxx = 0; xxx < line.size()-1; xxx+=2) {
			tmp[0] = line[xxx];
			tmp[1] = line[xxx+1];
			int32_t val = 0;
			sscanf(tmp, "%x", &val);
			_ouputImage.set(ivec2(xxx/2, currentLineId), etk::Color<>((uint8_t)val, (uint8_t)val, (uint8_t)val, (uint8_t)val));
		}
		++currentLineId;
	}
	if (line.size() > 0) {
		for (size_t xxx = 0; xxx < line.size()-1; xxx+=2) {
			tmp[0] = line[xxx];
			tmp[1] = line[xxx+1];
			int32_t val = 0;
			sscanf(tmp, "%x", &val);
			_ouputImage.set(ivec2(xxx/2, currentLineId), etk::Color<>((uint8_t)val, (uint8_t)val, (uint8_t)val, (uint8_t)val));
		}
	}
	file.fileClose();
	return true;
}

bool egami::storeEDF(const std::string& _fileName, const egami::Image& _inputImage) {
	bool anErrorEccured = false;
	etk::FSNode file(_fileName);
	if (file.fileOpenWrite() == false) {
		EGAMI_ERROR("Can not find the file name=\"" << file << "\"");
		return false;
	}
	anErrorEccured = file.filePuts(   std::string("#EDF // Generate with EGAMI (")
	                                + etk::to_string(_inputImage.getSize().x())
	                                + ","
	                                + etk::to_string(_inputImage.getSize().y()) + ")\n");
	
	char tmp[256];
	for (int32_t yyy = 0; yyy < _inputImage.getSize().y(); ++yyy) {
		if (yyy != 0) {
			if (file.filePut('\n') == false) {
				anErrorEccured = false;
			}
		}
		for (int32_t xxx = 0; xxx < _inputImage.getSize().x(); ++xxx) {
			sprintf(tmp, "%02X", _inputImage.get(ivec2(xxx, yyy)).a());
			/*
			if (yyy == 25) {
				EGAMI_DEBUG(" set : " << _inputImage.get(ivec2(xxx, yyy)) << " : '" << tmp << "'");
			}
			*/
			if (file.filePuts(tmp) == false) {
				anErrorEccured = false;
			}
		}
	}
	
	file.fileClose();
	return anErrorEccured;
}
