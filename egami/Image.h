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
#include <vector>
#include <etk/math/Vector2D.h>
#include <etk/Color.h>

namespace egami {
	class Image {
		private:
			ivec2 m_size;
			std::vector<etk::Color<> > m_data;
		public:
			// constructor :
			Image(const ivec2& _size=ivec2(32,32));
			// destructor
			~Image(void) { };
		// EWOL internal API for Texture system :
		public:
			void* getTextureDataPointer(void) {
				return &m_data[0];
			};
		// -----------------------------------------------
		// -- basic tools :
		// -----------------------------------------------
		public :
			void resize(const ivec2& _size, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<>& _color);
			
			const ivec2& getSize(void) const {
				return m_size;
			};
			int32_t getWidth(void) const {
				return m_size.x();
			};
			int32_t getHeight(void) const {
				return m_size.y();
			};
			void clear(etk::Color<> _fill);
			const etk::Color<>& get(const ivec2& _pos) const;
			void set(const ivec2& _pos, const etk::Color<>& _newColor);
			void insert(const ivec2& _pos, const egami::Image& _input);
			/**
			 * @brief Scale an image in an other dimention.
			 * @param[in] _size Destination size of the image.
			 * @TODO Set this function more capacity like not a multiple ratio...
			 */
			void scale(const ivec2& _size);
	};
	
};

#endif

