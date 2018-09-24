/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperSVG.hpp>
#include <etk/uri/uri.hpp>
#include <esvg/esvg.hpp>


egami::Image egami::loadSVG(const etk::Uri& _uri, const ivec2& _size) {
	egami::Image out;
	esvg::Document svgDocument;
	if (svgDocument.load(_uri) == false) {
		EGAMI_ERROR("Error to load SVG file " << _uri );
		return out;
	}
	ivec2 imageSize = _size;
	#if 0
		etk::Vector<etk::Color<float,4>> svgImage = svgDocument.renderImageFloatRGBA(imageSize);
		out.configure(imageSize, egami::colorType::RGBAf);
		out.set(svgImage, imageSize);
	#else
		etk::Vector<etk::Color<uint8_t,4>> svgImage = svgDocument.renderImageU8RGBA(imageSize);
		out.configure(imageSize, egami::colorType::RGBA8);
		out.set(svgImage, imageSize);
	#endif
	return out;
}