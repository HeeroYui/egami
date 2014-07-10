/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_IMAGE_PRIVATE_H__
#define __EGAMI_IMAGE_PRIVATE_H__

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>

namespace egami {
	class ImagePrivate {
		public:
			ImagePrivate() {};
			virtual ~ImagePrivate() {};
			virtual void* getTextureDataPointer() { return nullptr; };
			virtual const ivec2& getSize()=0;
			virtual int32_t getWidth() const { return 0; };
			virtual int32_t getHeight() const { return 0; };
			virtual enum colorType getType() { return colorRGBA8; };
			virtual void clear() = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint8_t, 4>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<float, 4>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const ivec2& _startPos) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<float>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) = 0;
			virtual etk::Color<> get(const ivec2& _pos) const = 0;
	};
	
	template<typename T = etk::Color<>>
	class ImageTemplate : public ImagePrivate {
		private:
			ivec2 m_size;
			std::vector<T> m_data;
		public:
			// constructor :
			ImageTemplate(const ivec2& _size=ivec2(32,32)) :
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
			
			// destructor
			virtual ~ImageTemplate() { };
		// EWOL internal API for Texture system :
		public:
			void* getTextureDataPointer() {
				return &m_data[0];
			};
			enum colorType getType();
			const ivec2& getSize() { return m_size; };
		// -----------------------------------------------
		// -- basic tools :
		// -----------------------------------------------
		public :
			void resize__(const ivec2& _size, const ivec2& _startPos=ivec2(0,0)) {
				if (_size == m_size) {
					// same size  == > nothing to do ...
					return;
				}
				if ((size_t)(_size.x()*_size.y()) > m_data.size()) {
					m_data.resize(_size.x()*_size.y());
				}
				// grow size :
				if (_size.x() == m_size.x()) {
					if (_size.y() < m_size.y()) {
						// Just remove lines ....
					} else {
						// just add lines
					}
				} else if (_size.x() < m_size.x()) {
					if (_size.y() <= m_size.y()) {
						for (int32_t yyy=0; yyy<_size.y(); ++yyy) {
							for (int32_t xxx=0; xxx<_size.x(); ++xxx) {
								m_data[yyy*_size.x()+xxx] = m_data[yyy*m_size.x()+xxx];
							}
						}
					} else {
						for (int32_t yyy=m_size.y()-1; yyy>=0; --yyy) {
							for (int32_t xxx=0; xxx<_size.x(); ++xxx) {
								m_data[yyy*_size.x()+xxx] = m_data[yyy*m_size.x()+xxx];
							}
						}
					}
				} else { // (_size.x() > m_size.x())
					
					if (_size.y() <= m_size.y()) {
						for (int32_t yyy=0; yyy<_size.y(); ++yyy) {
							for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
								m_data[yyy*_size.x()+xxx] = m_data[yyy*m_size.x()+xxx];
							}
						}
					} else {
						for (int32_t yyy=m_size.y()-1; yyy>=0; --yyy) {
							for (int32_t xxx=0; xxx<m_size.x(); ++xxx) {
								m_data[yyy*_size.x()+xxx] = m_data[yyy*m_size.x()+xxx];
							}
						}
					}
				}
				if ((size_t)(_size.x()*_size.y()) < m_data.size()) {
					m_data.resize(_size.x()*_size.y());
				}
				m_size = _size;
			}
			void resize__(const ivec2& _size, const T& _color) {
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
			
			void resize(const ivec2& _size, const ivec2& _startPos) {
				resize__(_size);
			}
			template<typename TYPE_2> void resize(const ivec2& _size, const TYPE_2& _color) {
				T tmp(_color);
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
			void clearColor(const T& _fill) {
				for (int32_t iii=0; iii<m_size.x()*m_size.y(); iii++) {
					m_data[iii] = _fill;
				}
			}
			void clear() {
				clearColor(T::emptyColor);
			}
			etk::Color<> get(const ivec2& _pos) const {
				return get__(_pos);
			}
			
			const T& get__(const ivec2& _pos) const {
				static const T errorColor(0x00000000);
				if(    _pos.x()>0 && _pos.x()<m_size.x()
				    && _pos.y()>0 && _pos.y()<m_size.y()) {
					return m_data[_pos.x()+_pos.y()*m_size.x()];
				}
				return errorColor;
			}
			void set__(const ivec2& _pos, const T& _newColor) {
				if(    _pos.x()>=0 && _pos.x()<m_size.x()
				    && _pos.y()>=0 && _pos.y()<m_size.y()) {
					m_data[_pos.x()+_pos.y()*m_size.x()] = _newColor;
				}
			}
			void insert(const ivec2& _pos, const ImageTemplate<T>& _input) {
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
	};
	template <> enum colorType ImageTemplate<etk::Color<uint8_t>>::getType() {
		return colorRGBA8;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint8_t, 3>>::getType() {
		return colorRGB8;
	}
	template <> enum colorType ImageTemplate<etk::Color<float>>::getType() {
		return colorRGBAf;
	}
	template <> enum colorType ImageTemplate<etk::Color<float, 3>>::getType() {
		return colorRGBf;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint16_t, 1>>::getType() {
		return colorU16;
	}
	template <> enum colorType ImageTemplate<etk::Color<uint32_t, 1>>::getType() {
		return colorU32;
	}
	template <> enum colorType ImageTemplate<etk::Color<float, 1>>::getType() {
		return colorFloat;
	}
	template <> enum colorType ImageTemplate<etk::Color<double, 1>>::getType() {
		return colorDouble;
	}
};

#endif
