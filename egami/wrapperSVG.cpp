/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <egami/debug.h>
#include <egami/Image.h>
#include <egami/wrapperSVG.h>
#include <etk/os/FSNode.h>
#include <esvg/esvg.h>


#undef __class__
#define __class__	"wrapperSVG"


bool egami::loadSVG(const std::string& _fileName, egami::Image& _ouputImage, const ivec2& _size) {
	esvg::Document svgDocument;
	if (svgDocument.load(_fileName) == false) {
		EGAMI_ERROR("Error to load SVG file " << _fileName );
		return false;
	}
	ivec2 imageSize = _size;
	std::vector<etk::Color<float,4>> svgImage = svgDocument.renderImageFloatRGBA(imageSize);
	_ouputImage.set(svgImage, imageSize);
	return true;
}