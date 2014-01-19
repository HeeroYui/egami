/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <egami/Image.h>
#include <egami/debug.h>

egami::Image::Image(const ivec2& _size) :
    m_size(_size) {
	// basic element :
	etk::Color<> tmpBg(0,0,0,0);
	// preallocate data with a basic bg elements :
	m_data.resize(m_size.x()*m_size.y(), tmpBg);
	if ((uint32_t)m_size.x()*m_size.y() > m_data.size()) {
		TK_ERROR("Allocation of data buffer in error");
		return;
	}
}

void egami::Image::resize(const ivec2& _size, const etk::Color<>& _color) {
	m_size=_size;
	m_data.resize(m_size.x()*m_size.y(), _color);
}

void egami::Image::resize(const ivec2& _size, const ivec2& _startPos) {
	if (_size == m_size) {
		// same size  == > nothing to do ...
		return;
	}
	// grow size :
	egami::Image tmpImage(*this);
	m_size=_size;
	etk::Color<> tmpBg(0,0,0,0);
	m_data.resize(m_size.x()*m_size.y(), tmpBg);
	for (int32_t jjj=0; jjj<m_size.y(); jjj++) {
		for (int32_t iii=0; iii<m_size.y(); iii++) {
			ivec2 tmppos(iii,jjj);
			set(tmppos, tmpImage.get(tmppos));
		}
	}
}

void egami::Image::scale(const ivec2& _size) {
	// TODO : Add capabilities ...
	int32_t stepX = m_size.x() / _size.x();
	int32_t stepY = m_size.y() / _size.y();
	stepX = etk_max(1, stepX);
	stepY = etk_max(1, stepY);
	EGAMI_VERBOSE("move : " << stepX << " , " << stepY << " from : " << m_size << " ==> " << _size);
	for (int32_t yyy = 0; yyy < _size.y(); ++yyy) {
		for (int32_t xxx = 0; xxx < _size.x(); ++xxx) {
			set(ivec2(xxx, yyy), get(ivec2(xxx*stepX, yyy*stepY)));
		}
	}
	resize(_size);
}


void egami::Image::clear(etk::Color<> _fill) {
	for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
		m_data[iii] = _fill;
	}
}
const etk::Color<>& egami::Image::get(const ivec2& _pos) const {
	static const etk::Color<> errorColor(0x00000000);
	if(    _pos.x()>0 && _pos.x()<m_size.x()
	    && _pos.y()>0 && _pos.y()<m_size.y()) {
		return m_data[_pos.x()+_pos.y()*m_size.x()];
	}
	return errorColor;
}

void egami::Image::set(const ivec2& _pos, const etk::Color<>& _newColor) {
	if(    _pos.x()>=0 && _pos.x()<m_size.x()
	    && _pos.y()>=0 && _pos.y()<m_size.y()) {
		m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
	}
}

void egami::Image::insert(const ivec2& _pos, const egami::Image& _input) {
	for(int32_t yyy = 0; yyy < _input.getSize().y() && _pos.y() + yyy < m_size.y(); ++yyy) {
		for(int32_t xxx = 0; xxx < _input.getSize().x() && _pos.x() + xxx < m_size.x(); ++xxx) {
			set(ivec2(_pos.x()+xxx, _pos.y()+yyy), _input.get(ivec2(xxx, yyy)) );
		}
	}
}