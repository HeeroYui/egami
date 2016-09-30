/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <egami/ImageMono.hpp>
#include <egami/debug.hpp>

egami::ImageMono::ImageMono(const ivec2& _size) :
  m_size(_size) {
	// basic element :
	uint8_t tmpBg(0);
	// preallocate data with a basic bg elements :
	m_data.resize(m_size.x()*m_size.y(), tmpBg);
	if ((uint32_t)m_size.x()*m_size.y() > m_data.size()) {
		EGAMI_ERROR("Allocation of data buffer in error");
		return;
	}
}

void egami::ImageMono::resize(const ivec2& _size, const uint8_t& _color) {
	m_size=_size;
	m_data.resize(m_size.x()*m_size.y(), _color);
}

void egami::ImageMono::resize(const ivec2& _size, const ivec2& _startPos) {
	if (_size == m_size) {
		// same size  == > nothing to do ...
		return;
	}
	// grow size :
	egami::ImageMono tmpImage(*this);
	m_size=_size;
	uint8_t tmpBg(0);
	m_data.resize(m_size.x()*m_size.y(), tmpBg);
	for (int32_t jjj=0; jjj<m_size.y(); jjj++) {
		for (int32_t iii=0; iii<m_size.y(); iii++) {
			ivec2 tmppos(iii,jjj);
			set(tmppos, tmpImage.get(tmppos));
		}
	}
}


void egami::ImageMono::clear(uint8_t _fill) {
	for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
		m_data[iii] = _fill;
	}
}
const uint8_t& egami::ImageMono::get(const ivec2& _pos) const {
	static const uint8_t errorColor(0x00000000);
	if(    _pos.x()>0 && _pos.x()<m_size.x()
	    && _pos.y()>0 && _pos.y()<m_size.y()) {
		return m_data[_pos.x()+_pos.y()*m_size.x()];
	}
	return errorColor;
}

void egami::ImageMono::set(const ivec2& _pos, const uint8_t& _newColor) {
	if(    _pos.x()>=0 && _pos.x()<m_size.x()
	    && _pos.y()>=0 && _pos.y()<m_size.y()) {
		m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
	}
}
