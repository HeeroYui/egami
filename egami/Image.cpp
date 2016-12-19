/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <egami/Image.hpp>
#include <egami/debug.hpp>
#include <egami/ImagePrivate.hpp>
#include <ememory/memory.hpp>

std::ostream& egami::operator <<(std::ostream& _os, const enum egami::colorType _type) {
	switch (_type) {
		case egami::colorType::undefined:
			_os << "egami::colorType::undefined";
			break;
		case egami::colorType::RGBA8:
			_os << "egami::colorType::RGBA8";
			break;
		case egami::colorType::RGB8:
			_os << "egami::colorType::RGB8";
			break;
		case egami::colorType::RGBAf:
			_os << "egami::colorType::RGBAf";
			break;
		case egami::colorType::RGBf:
			_os << "egami::colorType::RGBf";
			break;
		case egami::colorType::unsignedInt16:
			_os << "egami::colorType::unsignedInt16";
			break;
		case egami::colorType::unsignedInt32:
			_os << "egami::colorType::unsignedInt32";
			break;
		case egami::colorType::float32:
			_os << "egami::colorType::float32";
			break;
		case egami::colorType::float64:
			_os << "egami::colorType::float64";
			break;
	}
	return _os;
}

int32_t egami::getFormatColorSize(enum colorType _type) {
	switch (_type) {
		case egami::colorType::undefined:
			return 1;
			break;
		case egami::colorType::RGBA8:
			return 1*4;
			break;
		case egami::colorType::RGB8:
			return 1*3;
			break;
		case egami::colorType::RGBAf:
			return 4*4;
			break;
		case egami::colorType::RGBf:
			return 4*3;
			break;
		case egami::colorType::unsignedInt16:
			return 2;
			break;
		case egami::colorType::unsignedInt32:
			return 4;
			break;
		case egami::colorType::float32:
			return 4;
			break;
		case egami::colorType::float64:
			return 8;
			break;
	}
	return 1;
}

egami::Image::Image() :
  m_data(nullptr) {
	
}

egami::Image::~Image() {
	
}

egami::Image::Image(const ivec2& _size, enum colorType _type) :
  m_data(nullptr) {
	configure(_size, _type);
}

void egami::Image::swap(egami::Image& _obj) {
	ememory::SharedPtr<ImagePrivate> tmp = m_data;
	m_data = _obj.m_data;
	_obj.m_data = tmp;
}

void egami::Image::configure(const ivec2& _size, enum colorType _type) {
	switch (_type) {
		case egami::colorType::undefined:
			m_data = nullptr;
			break;
		case egami::colorType::RGBA8:
			//m_data = ememory::makeShared<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint8_t>>(_size));
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<uint8_t>>>(_size);
			break;
		case egami::colorType::RGB8:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<uint8_t, 3>>>(_size);
			break;
		case egami::colorType::RGBAf:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<float>>>(_size);
			break;
		case egami::colorType::RGBf:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<float, 3>>>(_size);
			break;
		case egami::colorType::unsignedInt16:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<uint16_t, 1>>>(_size);
			break;
		case egami::colorType::unsignedInt32:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<uint32_t, 1>>>(_size);
			break;
		case egami::colorType::float32:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<float, 1>>>(_size);
			break;
		case egami::colorType::float64:
			m_data = ememory::makeShared<egami::ImageTemplate<etk::Color<double, 1>>>(_size);
			break;
	}
}

enum egami::colorType egami::Image::getType() const {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return egami::colorType::undefined;
	}
	return m_data->getType();
}

void* egami::Image::getTextureDataPointer() {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return nullptr;
	}
	return m_data->getTextureDataPointer();
}

void egami::Image::resize(const ivec2& _size, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _startPos);
}

void egami::Image::resize(const ivec2& _size, const etk::Color<>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}

const ivec2& egami::Image::getSize() const {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		static const ivec2 error(0,0);
		return error;
	}
	return m_data->getSize();
}

int32_t egami::Image::getWidth() const {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return 0;
	}
	return m_data->getWidth();
}

int32_t egami::Image::getHeight() const {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return 0;
	}
	return m_data->getHeight();
}


void egami::Image::scale(const ivec2& _size) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	resize(_size);
}

void egami::Image::clear(const etk::Color<>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<float>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<uint16_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<uint32_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<float, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<double, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->clear();
};

etk::Color<> egami::Image::get(const ivec2& _pos) const {
	if (m_data == nullptr) {
		return etk::Color<>(0,0,0,0);
	}
	return m_data->get(_pos);;
}

void egami::Image::insert(const ivec2& _pos, const egami::Image& _input) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	if (_input.m_data == nullptr) {
		EGAMI_DEBUG("No input data for image (nullptr)");
		return;
	}
	enum colorType destType = m_data->getType();
	enum colorType sourceType = _input.m_data->getType();
	if (destType == sourceType) {
		for (int32_t yyy=0; yyy < _input.getHeight(); ++yyy) {
			for (int32_t xxx=0; xxx < _input.getWidth(); ++xxx) {
				m_data->set(ivec2(_pos.x()+xxx,_pos.y()+yyy), _input.m_data->get(ivec2(xxx,yyy)));
				//EGAMI_INFO("copy : " << ivec2(xxx,yyy) << " => " << ivec2(_pos.x()+xxx,_pos.y()+yyy));
			}
		}
	} else {
		EGAMI_CRITICAL("TODO : Insert image");
	}
}

void egami::Image::set(const ivec2& _pos, const etk::Color<>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const std::vector<etk::Color<float,4>>& _data, const ivec2& _size) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_data, _size);
}

void egami::Image::set(const std::vector<etk::Color<uint8_t,4>>& _data, const ivec2& _size) {
	if (m_data == nullptr) {
		EGAMI_DEBUG("No internal data for image (nullptr)");
		return;
	}
	m_data->set(_data, _size);
}

