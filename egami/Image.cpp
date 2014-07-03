/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
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
	switch(m_data->getType()) {
		case colorRGBA8: {
				std::shared_ptr<ImageTemplate<etk::Color<uint8_t>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<uint8_t>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorRGB8: {
				std::shared_ptr<ImageTemplate<etk::Color<uint8_t, 3>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<uint8_t, 3>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorRGBAf: {
				std::shared_ptr<ImageTemplate<etk::Color<float>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<float>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorRGBf: {
				std::shared_ptr<ImageTemplate<etk::Color<float, 3>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<float, 3>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorU16: {
				std::shared_ptr<ImageTemplate<etk::Color<uint8_t, 1>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<uint8_t, 1>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorU32: {
				std::shared_ptr<ImageTemplate<etk::Color<uint32_t, 1>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<uint32_t, 1>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorFloat: {
				std::shared_ptr<ImageTemplate<etk::Color<float, 1>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<float, 1>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
		case colorDouble: {
				std::shared_ptr<ImageTemplate<etk::Color<double, 1>>> tmp = std::dynamic_pointer_cast<ImageTemplate<etk::Color<double, 1>>>(m_data);
				tmp->resize(_size, _startPos);
			}
			break;
	}
}

void egami::Image::resize(const ivec2& _size, const etk::Color<>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<int16_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<int32_t, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}
void egami::Image::resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return;
	}
	//m_data->resize(_size, _color);
}

const ivec2& egami::Image::getSize() const {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not resize");
		return ivec2(0,0);
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
}

void egami::Image::clear(const etk::Color<>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};
void egami::Image::clear(const etk::Color<float>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};
void egami::Image::clear(const etk::Color<int16_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};
void egami::Image::clear(const etk::Color<int32_t, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};
void egami::Image::clear(const etk::Color<float, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};
void egami::Image::clear(const etk::Color<double, 1>& _color) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not clear");
		return;
	}
	
};

etk::Color<> egami::Image::get(const ivec2& _pos) const {
	if (m_data == nullptr) {
		return etk::Color<>(0,0,0,0);
	}
		return etk::Color<>(0,0,0,0);
}

void egami::Image::insert(const ivec2& _pos, const egami::Image& _input) {
	if (m_data == nullptr) {
		EGAMI_WARNING("No internal data for image : Can not insert image");
		return;
	}
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<>& _newColor) {
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float>& _newColor) {
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) {
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) {
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) {
	
}

void egami::Image::set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) {
	
}


