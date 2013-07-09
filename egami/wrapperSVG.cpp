/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <etk/types.h>
#include <egami/debug.h>
#include <egami/Image.h>
#include <egami/wrapperSVG.h>
#include <etk/os/FSNode.h>
#include <esvg/esvg.h>


#undef __class__
#define __class__	"wrapperSVG"


bool egami::LoadSVG(const etk::UString& _fileName, egami::Image& _ouputImage, const ivec2& _size)
{
	esvg::Document m_element(_fileName);
	if (false == m_element.IsLoadOk()) {
		EGAMI_ERROR("Error To load SVG file " << _fileName );
		return false;
	}
	draw::Image tmpImage;
	if(    _size.x()>0
	    && _size.y()>0 ) {
		m_element.GenerateAnImage(_size, tmpImage);
	} else {
		m_element.GenerateAnImage(tmpImage);
	}
	// generate the output image in the corect format:
	_ouputImage.Resize(tmpImage.GetSize(), etk::color::white);
	for (int32_t jjj=0; jjj<tmpImage.GetSize().y(); jjj++) {
		for (int32_t iii=0; iii<tmpImage.GetSize().y(); iii++) {
			ivec2 tmppos(iii,jjj);
			draw::Color tmpColor = tmpImage.Get(tmppos);
			_ouputImage.Set(tmppos, etk::Color<>(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a) );
		}
	}
	return true;
}