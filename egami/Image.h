/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EGAMI_IMAGE_H__
#define __EGAMI_IMAGE_H__

#include <etk/types.h>
#include <etk/Vector.h>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>

namespace egami
{
	class Image {
		private:
			ivec2 m_size;
			etk::Vector<etk::Color<> > m_data;
		public:
			// constructor :
			Image(const ivec2& _size=ivec2(32,32));
			// destructor
			~Image(void) { };
		// EWOL internal API for Texture system :
		public:
			void* GetTextureDataPointer(void) { return &m_data[0]; };
		// -----------------------------------------------
		// -- basic tools :
		// -----------------------------------------------
		public :
			void Resize(const ivec2& _size, const ivec2& _startPos=ivec2(0,0));
			void Resize(const ivec2& _size, const etk::Color<>& _color);
			
			const ivec2& GetSize(void) const { return m_size; };
			int32_t GetWidth(void) const { return m_size.x(); };
			int32_t GetHeight(void) const { return m_size.y(); };
			void Clear(etk::Color<> _fill);
			const etk::Color<>& Get(const ivec2& _pos) const;
			void Set(const ivec2& _pos, const etk::Color<>& _newColor);
	};
	
};

#endif

