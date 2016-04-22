/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#pragma once

#include <etk/types.h>
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>

namespace egami {
	class ImageMono {
		private:
			ivec2 m_size;
			std::vector<uint8_t> m_data;
		public:
			// constructor :
			ImageMono(const ivec2& _size=ivec2(32,32));
			// destructor
			~ImageMono() { };
		// EWOL internal API for Texture system :
		public:
			void* getTextureDataPointer() {
				return &m_data[0];
			};
			/*
			enum colorType getType() {
				return egami::colorType::unsignedInt8;
			};
			*/
		// -----------------------------------------------
		// -- basic tools :
		// -----------------------------------------------
		public :
			void resize(const ivec2& _size, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const uint8_t& _color);
			
			const ivec2& getSize() const {
				return m_size;
			};
			int32_t getWidth() const {
				return m_size.x();
			};
			int32_t getHeight() const {
				return m_size.y();
			};
			void clear(uint8_t _fill);
			const uint8_t& get(const ivec2& _pos) const;
			void set(const ivec2& _pos, const uint8_t& _newColor);
	};
}

