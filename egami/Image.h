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
#include <etk/stdTools.h>
#include <memory>

namespace egami {
	enum class colorType {
		RGBA8,
		RGB8,
		RGBAf,
		RGBf,
		//unsignedInt8,
		unsignedInt16,
		unsignedInt32,
		float32,
		float64,
	};
	std::ostream& operator <<(std::ostream& _os, const enum egami::colorType _obj);
	class ImagePrivate;
	class Image {
		private:
			std::shared_ptr<ImagePrivate> m_data; //!< data of the image
		public:
			// constructor :
			Image(const ivec2& _size=ivec2(32,32), enum colorType _type=egami::colorType::RGBA8);
			// destructor
			~Image() { };
		public:
			void configure(const ivec2& _size=ivec2(32,32), enum colorType _type=egami::colorType::RGBA8);
			void* getTextureDataPointer();
			enum colorType getType();
		// -----------------------------------------------
		// -- basic tools :
		// -----------------------------------------------
		public :
			void resize(const ivec2& _size, const ivec2& _startPos=ivec2(0,0));
			// TODO : Create a template function ...
			void resize(const ivec2& _size, const etk::Color<>& _color, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<float>& _color, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos=ivec2(0,0));
			void resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos=ivec2(0,0));
			
			const ivec2& getSize() const;
			int32_t getWidth() const;
			int32_t getHeight() const;
			void clear(const etk::Color<>& _color);
			void clear(const etk::Color<float>& _color);
			void clear(const etk::Color<uint16_t, 1>& _color);
			void clear(const etk::Color<uint32_t, 1>& _color);
			void clear(const etk::Color<float, 1>& _color);
			void clear(const etk::Color<double, 1>& _color);
			
			etk::Color<> get(const ivec2& _pos) const;
			/*
			etk::Color<> getRGBA8(const ivec2& _pos) const;
			etk::Color<float> getRGBAf(const ivec2& _pos) const;
			uint16_t getU16(const ivec2& _pos) const;
			uint32_t getU32(const ivec2& _pos) const;
			float getFloat(const ivec2& _pos) const;
			double getDouble(const ivec2& _pos) const;
			*/
			void set(const ivec2& _pos, const etk::Color<>& _newColor);
			void set(const ivec2& _pos, const etk::Color<float>& _newColor);
			void set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor);
			void set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor);
			void set(const ivec2& _pos, const etk::Color<float, 1>& _newColor);
			void set(const ivec2& _pos, const etk::Color<double, 1>& _newColor);
			void insert(const ivec2& _pos, const egami::Image& _input);
			/**
			 * @brief Scale an image in an other dimention.
			 * @param[in] _size Destination size of the image.
			 * @TODO Set this function more capacity like not a multiple ratio...
			 */
			void scale(const ivec2& _size);
			
			void set(const std::vector<etk::Color<float,4>>& _data, const ivec2& _size);
			void set(const std::vector<etk::Color<uint8_t,4>>& _data, const ivec2& _size);
	};
}


