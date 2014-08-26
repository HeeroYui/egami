/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <egami/Image.h>
#include <egami/debug.h>
#include <egami/ImagePrivate.h>
#include <memory>

egami::Image::Image(const ivec2& _size, enum colorType _type) :
  m_data(nullptr) {
	switch (_type) {
		case colorRGBA8:
			//m_data = std::make_shared<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint8_t>>(_size));
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint8_t>>(_size));
			break;
		case colorRGB8:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint8_t, 3>>(_size));
			break;
		case colorRGBAf:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<float>>(_size));
			break;
		case colorRGBf:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<float, 3>>(_size));
			break;
		case colorU16:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint16_t, 1>>(_size));
			break;
		case colorU32:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<uint32_t, 1>>(_size));
			break;
		case colorFloat:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<float, 1>>(_size));
			break;
		case colorDouble:
			m_data = std::shared_ptr<egami::ImagePrivate>(new egami::ImageTemplate<etk::Color<double, 1>>(_size));
			break;
	}
}

void* egami::Image::getTextureDataPointer() {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not get internal data pointer");
		return nullptr;
	}
	return m_data->getTextureDataPointer();
}

void egami::Image::resize(const ivec2& _size, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _startPos);
}

void egami::Image::resize(const ivec2& _size, const etk::Color<>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	m_data->resize(_size, _color, _startPos);
}

const ivec2& egami::Image::getSize() const {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		static const ivec2 error(0,0);
		return error;
	}
	return m_data->getSize();
}

int32_t egami::Image::getWidth() const {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return 0;
	}
	return m_data->getWidth();
}

int32_t egami::Image::getHeight() const {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return 0;
	}
	return m_data->getHeight();
}


void egami::Image::scale(const ivec2& _size) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not scale");
		return;
	}
	resize(_size);
}

void egami::Image::clear(const etk::Color<>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<float>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<uint16_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<uint32_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<float, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	m_data->clear();
};
void egami::Image::clear(const etk::Color<double, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
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
		EGAMI_WARNING("No internal data for image : Can not insert image");
		return;
	}
	if (_input.m_data == nullptr) {
		EGAMI_WARNING("No input data for image : Can not insert nullptr image");
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
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}

void egami::Image::set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not set color");
		return;
	}
	m_data->set(_pos, _newColor);
}


