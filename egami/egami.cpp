/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <egami/egami.h>
#include <egami/debug.h>

#include <egami/wrapperSVG.h>
#include <egami/wrapperPNG.h>
#include <egami/wrapperBMP.h>

bool egami::scalable(const std::string& _fileName) {
	if (true ==  end_with(_fileName, ".svg") ) {
		return true;
	}
	return false;
}

bool egami::load(egami::Image& _output, const std::string& _fileName, const ivec2& _size) {
	std::string tmpName = std::tolower(_fileName);
	// select the corect Loader :
	if (true == end_with(tmpName, ".bmp") ) {
		if (false == egami::loadBMP(_fileName, _output)) {
			EGAMI_ERROR("Error to load BMP file '" << _fileName << "'");
			return false;
		}
	} else if (true == end_with(tmpName, ".svg") ) {
		if (false == egami::loadSVG(_fileName, _output, _size)) {
			EGAMI_ERROR("Error to load SVG file '" << _fileName << "'");
			return false;
		}
	} else if (true == end_with(tmpName, ".png") ) {
		if (false == egami::loadPNG(_fileName, _output)) {
			EGAMI_ERROR("Error to load PNG file '" << _fileName << "'");
			return false;
		}
	} else {
		EGAMI_ERROR("Extention not managed '" << _fileName << "' Sopported extention : .bmp / .svg / .png");
		return false;
	}
	return true;
}

bool egami::store(const egami::Image& _input, const std::string& _fileName) {
	std::string tmpName = std::tolower(_fileName);
	// select the corect Loader :
	if (true == end_with(tmpName, ".bmp") ) {
		if (false == egami::storeBMP(_fileName, _input)) {
			EGAMI_ERROR("Error to load BMP file '" << _fileName << "'");
			return false;
		}
	} else if (true == end_with(tmpName, ".svg") ) {
		EGAMI_ERROR("Can not store in SVG file '" << _fileName << "'");
		return false;
	} else if (true == end_with(tmpName, ".png") ) {
		EGAMI_ERROR("Can not store in PNG file '" << _fileName << "'");
		return false;
	} else {
		EGAMI_ERROR("Extention not managed '" << _fileName << "' Sopported extention : .bmp / .svg / .png");
		return false;
	}
	return true;
}
