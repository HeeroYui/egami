/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/Color.hpp>
#include <egami/debug.hpp>

#include <vector>

namespace egami {
	
	template<typename EGAMI_TYPE_COLOR = etk::Color<>>
	class ImageTemplate : public ImagePrivate {
		private:
			ivec2 m_size;
			std::vector<EGAMI_TYPE_COLOR> m_data;
		public:
			// constructor :
			ImageTemplate(const ivec2& _size=ivec2(32,32)) :
			  m_size(_size) {
				// basic element:
				etk::Color<> tmpBg(0,0,0,0);
				// preallocate data with a basic bg elements:
				m_data.resize(m_size.x()*m_size.y(), tmpBg);
				if ((uint32_t)m_size.x()*m_size.y() > m_data.size()) {
					//TK_ERROR("Allocation of data buffer in error");
					return;
				}
			}
			
			// destructor
			virtual ~ImageTemplate() { };
		// EWOL internal API for Texture system:
		public:
			void* getTextureDataPointer() {
				return &m_data[0];
			};
			enum colorType getType() const;
			const ivec2& getSize() {
				return m_size;
			};
		// -----------------------------------------------
		// -- basic tools:
		// -----------------------------------------------
		public :
			void resize2__(const ivec2& _size, const ivec2& _startPos=ivec2(0,0)) {
				if (_size == m_size) {
					// same size  == > nothing to do ...
					return;
				}
				ivec2 oldSize = m_size;
				m_size = _size;
				if ((size_t)(m_size.x()*m_size.y()) > m_data.size()) {
					m_data.resize(m_size.x()*m_size.y());
				}
				// grow size :
				if (m_size.x() == oldSize.x()) {
					if (m_size.y() < oldSize.y()) {
						// Just remove lines ....
					} else {
						// just add lines
					}
				} else if (m_size.x() < oldSize.x()) {
					if (m_size.y() <= oldSize.y()) {
						for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
							for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
								m_data[yyy*m_size.x()+xxx] = m_data[yyy*oldSize.x()+xxx];
							}
						}
					} else {
						for (int32_t yyy=oldSize.y()-1; yyy>=0; --yyy) {
							for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
								m_data[yyy*m_size.x()+xxx] = m_data[yyy*oldSize.x()+xxx];
							}
						}
					}
				} else { // (m_size.x() > oldSize.x())
					
					if (m_size.y() <= oldSize.y()) {
						for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
							for (int32_t xxx=0; xxx<oldSize.x(); ++xxx) {
								m_data[yyy*m_size.x()+xxx] = m_data[yyy*oldSize.x()+xxx];
							}
						}
					} else {
						for (int32_t yyy=oldSize.y()-1; yyy>=0; --yyy) {
							for (int32_t xxx=oldSize.x()-1; xxx>=0; --xxx) {
								m_data[yyy*m_size.x()+xxx] = m_data[yyy*oldSize.x()+xxx];
							}
						}
					}
				}
				if ((size_t)(m_size.x()*m_size.y()) < m_data.size()) {
					m_data.resize(m_size.x()*m_size.y());
				}
				// Clean all Data outside old range:
				// basic element:
				etk::Color<> tmpBg(0,0,0,0);
				for (int32_t yyy=oldSize.y(); yyy<m_size.y(); ++yyy) {
					for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
						set(ivec2(xxx,yyy), tmpBg);
					}
					if (yyy==oldSize.y()) {
						for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
							set(ivec2(xxx,yyy), etk::Color<>(m_data[(yyy-1)*oldSize.x()+xxx]));
						}
					}
				}
				for (int32_t xxx=oldSize.x(); xxx<m_size.x(); ++xxx) {
					for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
						set(ivec2(xxx,yyy), tmpBg);
					}
					if (xxx==oldSize.x()) {
						for (int32_t yyy=0; yyy<m_size.y(); ++yyy) {
							set(ivec2(xxx,yyy), etk::Color<>(m_data[yyy*oldSize.x()+oldSize.x()-1]));
						}
					}
				}
			}
			void resize__(const ivec2& _size, const EGAMI_TYPE_COLOR& _color) {
				m_size=_size;
				m_data.resize(m_size.x()*m_size.y(), _color);
			}
			
			void resize(const ivec2& _size, const etk::Color<uint8_t, 4>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			void resize(const ivec2& _size, const etk::Color<float, 4>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			void resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			void resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			void resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			void resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) {
				resize__(_size, _color);
			}
			
			void resize2(const ivec2& _size, const ivec2& _startPos) {
				resize2__(_size, _startPos);
			}
			template<typename EGAMI_TYPE_COLOR_2> void resize(const ivec2& _size, const EGAMI_TYPE_COLOR_2& _color) {
				EGAMI_TYPE_COLOR tmp(_color);
				resize__(_size, tmp);
			}
			void set(const ivec2& _pos, const etk::Color<>& _newColor) {
				set__(_pos, _newColor);
			}
			void set(const ivec2& _pos, const etk::Color<float>& _newColor) {
				set__(_pos, _newColor);
			}
			void set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) {
				set__(_pos, _newColor);
			}
			void set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) {
				set__(_pos, _newColor);
			}
			void set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) {
				set__(_pos, _newColor);
			}
			void set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) {
				set__(_pos, _newColor);
			}
			
			const ivec2& getSize() const {
				return m_size;
			};
			int32_t getWidth() const {
				return m_size.x();
			};
			int32_t getHeight() const {
				return m_size.y();
			};
			void clearColor(const EGAMI_TYPE_COLOR& _fill) {
				for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
					m_data[iii] = _fill;
				}
			}
			void clear() {
				clearColor(EGAMI_TYPE_COLOR::emptyColor);
			}
			etk::Color<> get(const ivec2& _pos) const {
				return get__(_pos);
			}
			
			const EGAMI_TYPE_COLOR& get__(const ivec2& _pos) const {
				static const EGAMI_TYPE_COLOR errorColor(0x00000000);
				if(    _pos.x()>=0 && _pos.x()<m_size.x()
				    && _pos.y()>=0 && _pos.y()<m_size.y()) {
					return m_data[_pos.x()+_pos.y()*m_size.x()];
				}
				return errorColor;
			}
			void set__(const ivec2& _pos, const EGAMI_TYPE_COLOR& _newColor) {
				if(    _pos.x()>=0 && _pos.x()<m_size.x()
				    && _pos.y()>=0 && _pos.y()<m_size.y()) {
					m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
				}
			}
			void insert(const ivec2& _pos, const ImageTemplate<EGAMI_TYPE_COLOR>& _input) {
				for(int32_t yyy = 0; yyy < _input.getSize().y() && _pos.y() + yyy < m_size.y(); ++yyy) {
					for(int32_t xxx = 0; xxx < _input.getSize().x() && _pos.x() + xxx < m_size.x(); ++xxx) {
						set(ivec2(_pos.x()+xxx, _pos.y()+yyy), _input.get(ivec2(xxx, yyy)) );
					}
				}
			}
			/**
			 * @brief Scale an image in an other dimention.
			 * @param[in] _size Destination size of the image.
			 * @TODO Set this function more capacity like not a multiple ratio...
			 */
			void scale(const ivec2& _size) {
				// TODO : Add capabilities ...
				int32_t stepX = m_size.x() / _size.x();
				int32_t stepY = m_size.y() / _size.y();
				stepX = std::max(1, stepX);
				stepY = std::max(1, stepY);
				EGAMI_VERBOSE("move : " << stepX << " , " << stepY << " from : " << m_size << " ==> " << _size);
				for (int32_t yyy = 0; yyy < _size.y(); ++yyy) {
					for (int32_t xxx = 0; xxx < _size.x(); ++xxx) {
						set(ivec2(xxx, yyy), get(ivec2(xxx*stepX, yyy*stepY)));
					}
				}
				resize(_size);
			}
			void set(const std::vector<etk::Color<float,4>>& _data, const ivec2& _size) {
				m_data.clear();
				m_size = _size;
				m_data.resize(_data.size());
				for (size_t iii=0; iii<m_data.size(); ++iii) {
					m_data[iii] = _data[iii];
				}
			}
			void set(const std::vector<etk::Color<uint8_t,4>>& _data, const ivec2& _size) {
				m_data.clear();
				m_size = _size;
				m_data.resize(_data.size());
				for (size_t iii=0; iii<m_data.size(); ++iii) {
					m_data[iii] = _data[iii];
				}
			}
	};
	template <> enum colorType ImageTemplate<etk::Color<uint8_t>>::getType() const {
		return egami::colorType::RGBA8;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint8_t, 3>>::getType() const {
		return egami::colorType::RGB8;
	}
	template <> enum colorType ImageTemplate<etk::Color<float>>::getType() const {
		return egami::colorType::RGBAf;
	}
	template <> enum colorType ImageTemplate<etk::Color<float, 3>>::getType() const {
		return egami::colorType::RGBf;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint16_t, 1>>::getType() const {
		return egami::colorType::unsignedInt16;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint32_t, 1>>::getType() const {
		return egami::colorType::unsignedInt32;
	}
	template <> enum colorType ImageTemplate<etk::Color<float, 1>>::getType() const {
		return egami::colorType::float32;
	}
	template <> enum colorType ImageTemplate<etk::Color<double, 1>>::getType() const {
		return egami::colorType::float64;
	}
};

