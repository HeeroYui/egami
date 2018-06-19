/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <etk/Vector.hpp>
#include <etk/math/Vector2D.hpp>
#include <etk/Color.hpp>
#include <etk/stdTools.hpp>
#include <ememory/memory.hpp>

namespace egami {
	enum class colorType {
		undefined,
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
	etk::Stream& operator <<(etk::Stream& _os, const enum egami::colorType _obj);
	/**
	 * @brief Get the Color size use in octet
	 * @param[in] type of the color
	 * @return Number of byte requested by the color
	 */
	int32_t getFormatColorSize(enum colorType _type);
	
	class ImagePrivate {
		public:
			ImagePrivate() {};
			virtual ~ImagePrivate() {};
			virtual void* getTextureDataPointer() const {
				return null;
			};
			virtual const ivec2& getSize() const = 0;
			virtual int32_t getWidth() const {
				return 0;
			};
			virtual int32_t getHeight() const {
				return 0;
			};
			virtual enum colorType getType() const {
				return egami::colorType::RGBA8;
			};
			virtual void clear() = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint8_t, 4>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<float, 4>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint16_t, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<uint32_t, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<float, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize(const ivec2& _size, const etk::Color<double, 1>& _color, const ivec2& _startPos) = 0;
			virtual void resize2(const ivec2& _size, const ivec2& _startPos) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<float>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<uint16_t, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<uint32_t, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<float, 1>& _newColor) = 0;
			virtual void set(const ivec2& _pos, const etk::Color<double, 1>& _newColor) = 0;
			virtual etk::Color<> get(const ivec2& _pos) const = 0;
			virtual void set(const etk::Vector<etk::Color<float,4>>& _data, const ivec2& _size) = 0;
			virtual void set(const etk::Vector<etk::Color<uint8_t,4>>& _data, const ivec2& _size) = 0;
	};
	
	class Image {
		private:
			// TODO : Change this in a unique_ptr ...
			ememory::SharedPtr<ImagePrivate> m_data; //!< data of the image
		public:
			/**
			 * @brief contructor that create an empty image (no valid data)
			 * @note use @ref configure to set a correct image
			 */
			Image();
			Image(const egami::Image& _image);
			Image& operator=(const egami::Image& _image);
			Image(const ivec2& _size,
			      enum colorType _type = egami::colorType::undefined,
			      const void* _dataToCopy = null);
			~Image();
			// TODO : IMplement move operator ... and copy operator...
		public:
			void configure(const ivec2& _size=ivec2(32,32),
			               enum colorType _type=egami::colorType::RGBA8);
			void* getTextureDataPointer() const;
			enum colorType getType() const;
			bool exist() {
				return m_data != null;
			}
			void swap(egami::Image& _obj);
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
			ivec2 getGPUSize() const;
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
			
			void set(const etk::Vector<etk::Color<float,4>>& _data, const ivec2& _size);
			void set(const etk::Vector<etk::Color<uint8_t,4>>& _data, const ivec2& _size);
	};
	etk::Stream& operator <<(etk::Stream& _os, const egami::Image& _obj);
}

