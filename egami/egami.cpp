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

bool egami::Scalable(const etk::UString& _fileName)
{
	if (true == _fileName.EndWith(".svg") ) {
		return true;
	}
	return false;
}

bool egami::Load(egami::Image& _output, const etk::UString& _fileName, const ivec2& _size)
{
	etk::UString tmpName = _fileName.ToLower();
	// select the corect Loader :
	if (true == tmpName.EndWith(".bmp") ) {
		if (false == egami::LoadBMP(_fileName, _output)) {
			EGAMI_ERROR("Error To load BMP file " << tmpName );
			return false;
		}
	} else if (true == tmpName.EndWith(".svg") ) {
		if (false == egami::LoadSVG(_fileName, _output, _size)) {
			EGAMI_ERROR("Error To load SVG file " << tmpName );
			return false;
		}
	} else if (true == tmpName.EndWith(".png") ) {
		if (false == egami::LoadPNG(_fileName, _output)) {
			EGAMI_ERROR("Error To load PNG file " << tmpName );
			return false;
		}
	} else {
		EGAMI_ERROR("Extention not managed " << tmpName << " Sopported extention : .bmp / .svg / .png");
		return false;
	}
	return true;
}
