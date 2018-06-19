/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperPNG.hpp>
#include <etk/os/FSNode.hpp>
#include <png/png.h>
namespace egami {
	class ReaderInstance {
		public:
			virtual ~ReaderInstance() = default;
			virtual void read(png_bytep _data, png_size_t _length) = 0;
			virtual void write(png_bytep _data, png_size_t _length) = 0;
			virtual void flush() = 0;
	};
	
	class ReaderInstanceFSNode : public egami::ReaderInstance {
		private:
			etk::FSNode& m_data;
		public:
			ReaderInstanceFSNode(etk::FSNode& _data):
			  m_data(_data) {
				
			}
			void read(png_bytep _data, png_size_t _length) override {
				m_data.fileRead(_data, 1, _length);
			}
			void write(png_bytep _data, png_size_t _length) override {
				m_data.fileWrite(_data, 1, _length);
			}
			void flush() override {
				m_data.fileFlush();
			}
	};
	
	class ReaderInstanceBuffer : public egami::ReaderInstance {
		private:
			etk::Vector<uint8_t>& m_data;
			int32_t m_offset;
		public:
			ReaderInstanceBuffer(const etk::Vector<uint8_t>& _data, int32_t _offset):
			  m_data(const_cast<etk::Vector<uint8_t>&>(_data)),
			  m_offset(_offset) {
				
			}
			ReaderInstanceBuffer(etk::Vector<uint8_t>& _data):
			  m_data(_data),
			  m_offset(0) {
				
			}
			void read(png_bytep data, png_size_t length) override {
				memcpy(data, &m_data[m_offset], length);
				m_offset += length;
			}
			void write(png_bytep _data, png_size_t _length) override {
				for (uint32_t iii=0; iii<_length; ++iii) {
					m_data.pushBack(_data[iii]);
					m_offset++;
				}
			}
			void flush() override {
				// nothing to do ...
			}
	};
}
// we must change the access of the IO of the png lib :
static void local_ReadData(png_structp _pngPtr, png_bytep _data, png_size_t _length) {
	egami::ReaderInstance* instance = static_cast<egami::ReaderInstance*>(png_get_io_ptr(_pngPtr));
	if (instance != null) {
		instance->read(_data, _length);
	}
}

static void Local_WriteData(png_structp _pngPtr, png_bytep _data, png_size_t _length) {
	egami::ReaderInstance* instance = static_cast<egami::ReaderInstance*>(png_get_io_ptr(_pngPtr));
	if (instance != null) {
		instance->write(_data, _length);
	}
}

static void local_FlushData(png_structp _pngPtr) {
	egami::ReaderInstance* instance = static_cast<egami::ReaderInstance*>(png_get_io_ptr(_pngPtr));
	if (instance != null) {
		instance->flush();
	}
}


void userErrorFunction(png_structp _pngPtr, png_const_charp _errorMsg) {
	EGAMI_ERROR("libpng error: '" << _errorMsg << "'");
}

void userWarningFunction(png_structp _pngPtr, png_const_charp _warningMsg) {
	EGAMI_WARNING("libpng warning: '" << _warningMsg << "'");
}

static egami::Image genericLoader(png_structp _pngPtr, png_infop _infoPtr) {
	egami::Image out;
	// If we have already read some of the signature
	png_set_sig_bytes(_pngPtr, 8);
	
	png_read_info(_pngPtr, _infoPtr);
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bit_depth = 0;
	int colorType = 0;
	int interlace_type = 0;
	png_get_IHDR(_pngPtr, _infoPtr, &width, &height, &bit_depth, &colorType, &interlace_type, null, null);
	// reallocate the image 
	EGAMI_ERROR("Load PNG image : (" << width << "," << height << ") bitDepth=" << bit_depth << " colorType=" << colorType);
	switch (colorType) {
		case PNG_COLOR_TYPE_RGBA:
			out.configure(ivec2(width,height), egami::colorType::RGBA8);
			break;
		case PNG_COLOR_TYPE_RGB:
			out.configure(ivec2(width,height), egami::colorType::RGB8);
			break;
		case PNG_COLOR_TYPE_GRAY:
			out.configure(ivec2(width,height), egami::colorType::RGB8);
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			out.configure(ivec2(width,height), egami::colorType::RGBA8);
			break;
		default:
			break;
	}
	
	// Tell libpng to strip 16 bits/color files down to 8 bits/color. Use accurate scaling if it's available, otherwise just chop off the low byte.
	#ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
		png_set_scale_16(_pngPtr);
	#else
		png_set_strip_16(_pngPtr);
	#endif
	
	// Strip alpha bytes from the input data without combining with the background (not recommended).
	//png_set_strip_alpha(_pngPtr);
	
	// Extract multiple pixels with bit depths of 1, 2, and 4 from a single byte into separate bytes (useful for paletted and grayscale images).
	png_set_packing(_pngPtr);
	
	// Change the order of packed pixels to least significant bit first (not useful if you are using png_set_packing).
	png_set_packswap(_pngPtr);
	
	/* Expand paletted colors into true RGB triplets */
	if (colorType == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(_pngPtr);
	}
	
	// Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel
	if (    colorType == PNG_COLOR_TYPE_GRAY
	     && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(_pngPtr);
	}
	
	// Expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if (png_get_valid(_pngPtr, _infoPtr, PNG_INFO_tRNS) != 0) {
		png_set_tRNS_to_alpha(_pngPtr);
	}
	
	/* Set the background color to draw transparent and alpha images over.
	 * It is possible to set the red, green, and blue components directly
	 * for paletted images instead of supplying a palette index.  Note that
	 * even if the PNG file supplies a background, you are not required to
	 * use it - you should use the (solid) application background if it has one.
	 */
	 /*
	png_color::16 my_background, *image_background;
	if (png_get_bKGD(_pngPtr, _infoPtr, &image_background) != 0) {
		png_set_background(_pngPtr, image_background, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
	} else {
		png_set_background(_pngPtr, &my_background, PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
	}
	*/
	/* Optional call to gamma correct and add the background to the palette
	 * and update info structure.  REQUIRED if you are expecting libpng to
	 * update the palette for you (ie you selected such a transform above).
	 */
	png_read_update_info(_pngPtr, _infoPtr);
	
	// Allocate the memory to hold the image using the fields of _infoPtr.
	// The easiest way to read the image:
	png_bytep row_pointers[height];
	/* Clear the pointer array */
	for (png_uint_32 row = 0; row < height; row++) {
		row_pointers[row] = null;
	}
	for (png_uint_32 row = 0; row < height; row++) {
		row_pointers[row] = (png_bytep)png_malloc(_pngPtr, png_get_rowbytes(_pngPtr, _infoPtr));
	}
	png_read_image(_pngPtr, row_pointers);
	// Read rest of file, and get additional chunks in _infoPtr - REQUIRED
	png_read_end(_pngPtr, _infoPtr);
	
	//png_set_expand(_pngPtr);

	etk::Color<> tmpColor(0,0,0,0);
	switch (colorType) {
		case PNG_COLOR_TYPE_RGBA:
			EGAMI_DEBUG("colorset: PNG_COLOR_TYPE_RGBA");
			// Conversion to OpenGL texture
			for (png_uint_32 yyy = 0; yyy < height; ++yyy) {
				png_byte* row = row_pointers[yyy];
				for (png_uint_32 xxx = 0; xxx < width; ++xxx) {
					png_byte* ptr = &(row[xxx*4]);
					tmpColor.set(ptr[0], ptr[1], ptr[2], ptr[3]);
					out.set(ivec2(xxx,yyy), tmpColor);
				}
			}
			break;
		case PNG_COLOR_TYPE_RGB:
			EGAMI_DEBUG("colorset: PNG_COLOR_TYPE_RGB");
			// Conversion to OpenGL texture
			for (png_uint_32 yyy = 0; yyy < height; ++yyy) {
				png_byte* row = row_pointers[yyy];
				for (png_uint_32 xxx = 0; xxx < width; ++xxx) {
					png_byte* ptr = &(row[xxx*3]);
					tmpColor.set(ptr[0], ptr[1], ptr[2]);
					out.set(ivec2(xxx,yyy), tmpColor);
				}
			}
			break;
		case PNG_COLOR_TYPE_GRAY:
			EGAMI_DEBUG("colorset: PNG_COLOR_TYPE_GRAY");
			// Conversion to OpenGL texture
			for (png_uint_32 yyy = 0; yyy < height; ++yyy) {
				png_byte* row = row_pointers[yyy];
				for (png_uint_32 xxx = 0; xxx < width; ++xxx) {
					png_byte* ptr = &(row[xxx]);
					tmpColor.set(ptr[0], ptr[0], ptr[0]);
					out.set(ivec2(xxx,yyy), tmpColor);
				}
			}
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			EGAMI_DEBUG("colorset: PNG_COLOR_TYPE_GRAY_ALPHA");
			// Conversion to OpenGL texture
			for (png_uint_32 yyy = 0; yyy < height; ++yyy) {
				png_byte* row = row_pointers[yyy];
				for (png_uint_32 xxx = 0; xxx < width; ++xxx) {
					png_byte* ptr = &(row[xxx*2]);
					tmpColor.set(ptr[0], ptr[0], ptr[0], ptr[1]);
					out.set(ivec2(xxx,yyy), tmpColor);
				}
			}
			break;
		default:
			EGAMI_ERROR("Must be RGB+alpha?/GRAY+alpha? not supported : " << (int64_t)png_get_color_type(_pngPtr, _infoPtr));
			if ((png_get_color_type(_pngPtr, _infoPtr) & PNG_COLOR_MASK_PALETTE) != 0) {
				EGAMI_ERROR("    palette");
			}
			if ((png_get_color_type(_pngPtr, _infoPtr) & PNG_COLOR_MASK_COLOR) != 0) {
				EGAMI_ERROR("    color");
			}
			if ((png_get_color_type(_pngPtr, _infoPtr) & PNG_COLOR_MASK_ALPHA) != 0) {
				EGAMI_ERROR("    Alpha");
			}
			return egami::Image();
	}
	// Clean up after the read, and free any memory allocated - REQUIRED
	png_destroy_read_struct(&_pngPtr, &_infoPtr, null);
	return out;
}


egami::Image egami::loadPNG(const etk::String& _inputFile) {
	egami::Image out;
	etk::FSNode fileName(_inputFile);
	if (fileName.exist() == false) {
		EGAMI_ERROR("File does not existed='" << fileName << "'");
		return out;
	}
	if(fileName.fileOpenRead() == false) {
		EGAMI_ERROR("Can not find the file name='" << fileName << "'");
		return out;
	}
	unsigned char header[8];
	
	if (fileName.fileRead(header,1,8) != 8) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return out;
	}
	if (png_sig_cmp(header, 0, 8)) {
		EGAMI_ERROR("Invalid file :" << fileName);
		return out;
	}
	
	// PNG read setup
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, userErrorFunction, userWarningFunction);
	if (png_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG structure");
		fileName.fileClose();
		return out;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG info structure");
		png_destroy_read_struct(&png_ptr, null, null);
		fileName.fileClose();
		return out;
	}
	/*
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR(" Can not set the JUMP buffer adresses");
		// Free all of the memory associated with the png_ptr and info_ptr
		png_destroy_read_struct(&png_ptr, &info_ptr, null);
		fileName.fileClose();
		return false;
	}
	*/
	ReaderInstanceFSNode tmpNode(fileName);
	
	ReaderInstance* tmpPoiter = &tmpNode;
	
	// overwrite the read function:
	png_set_read_fn(png_ptr,
	                tmpPoiter,
	                &local_ReadData);
	out = genericLoader(png_ptr, info_ptr);
	fileName.fileClose();
	return out;
}

egami::Image egami::loadPNG(const etk::Vector<uint8_t>& _buffer) {
	egami::Image out;
	if (png_sig_cmp(&_buffer[0], 0, 8)) {
		EGAMI_ERROR("Invalid start buffer:");
		return out;
	}
	
	// PNG read setup
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, null, userErrorFunction, userWarningFunction);
	if (png_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG structure");
		return out;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG info structure");
		png_destroy_read_struct(&png_ptr, null, null);
		return out;
	}
	egami::ReaderInstanceBuffer tmpNode(_buffer, 8);
	
	egami::ReaderInstance* tmpPoiter = &tmpNode;
	
	// Overwrite the read function:
	png_set_read_fn(png_ptr,
	                tmpPoiter,
	                &local_ReadData);
	out = genericLoader(png_ptr, info_ptr);
	return out;
}

bool genericWriter(png_structp png_ptr, png_infop info_ptr, const egami::Image& _inputImage) {
	//png_init_io(png_ptr, fp);
	/* write header */
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR("Error jump setting");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	png_byte bitDepth = 8;
	png_byte colorType = 0;
	switch(_inputImage.getType()) {
		case egami::colorType::RGBA8:
			colorType = PNG_COLOR_TYPE_RGB_ALPHA;
			//bitDepth = 4;
			break;
		case egami::colorType::RGB8:
			colorType = PNG_COLOR_TYPE_RGB;
			//bitDepth = 3;
			break;
		default:
			EGAMI_ERROR("PNG can not export an image with other type than RGB and RGBA request:" << _inputImage.getType());
			png_destroy_write_struct(&png_ptr, &info_ptr);
			return false;
	}
	png_set_IHDR(png_ptr,
	             info_ptr,
	             _inputImage.getSize().x(),
	             _inputImage.getSize().y(),
	             bitDepth,
	             colorType,
	             PNG_INTERLACE_NONE,
	             PNG_COMPRESSION_TYPE_BASE,
	             PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR("Error while writing byte");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	etk::Vector<png_bytep> rowPointers;
	rowPointers.resize(_inputImage.getSize().y(), NULL);
	uint8_t* imageData = (uint8_t*)_inputImage.getTextureDataPointer();
	for (size_t iii=0; iii<rowPointers.size(); ++iii) {
		rowPointers[iii] = &imageData[_inputImage.getSize().x()*getFormatColorSize(_inputImage.getType())*iii];
	}
	png_write_image(png_ptr, &rowPointers[0]);
	/* end write */
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR("Error while writing byte");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	return true;
}

bool egami::storePNG(etk::Vector<uint8_t>& _buffer, const egami::Image& _inputImage) {
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, userErrorFunction, userWarningFunction);
	if (png_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG structure");
		return false;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG info structure");
		png_destroy_write_struct(&png_ptr, null);
		return false;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR("Error during init_io");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}
	egami::ReaderInstanceBuffer tmpNode(_buffer);
	
	egami::ReaderInstance* tmpPointer = &tmpNode;
	
	// overwrite the write functions:
	png_set_write_fn(png_ptr,
	                 tmpPointer,
	                 &Local_WriteData,
	                 &local_FlushData);
	return genericWriter(png_ptr, info_ptr, _inputImage);
}

bool egami::storePNG(const etk::String& _fileName, const egami::Image& _inputImage) {
	etk::FSNode fileName(_fileName);
	if(fileName.fileOpenWrite() == false) {
		EGAMI_ERROR("Can not find the file name='" << fileName << "'");
		return false;
	}
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, userErrorFunction, userWarningFunction);
	if (png_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG structure");
		return false;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == null) {
		EGAMI_ERROR("Can not Allocate PNG info structure");
		png_destroy_write_struct(&png_ptr, null);
		fileName.fileClose();
		return false;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR("Error during init_io");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fileName.fileClose();
		return false;
	}
	ReaderInstanceFSNode tmpNode(fileName);
	
	ReaderInstance* tmpPoiter = &tmpNode;
	
	// overwrite the write functions:
	png_set_write_fn(png_ptr,
	                 tmpPoiter,
	                 &Local_WriteData,
	                 &local_FlushData);
	bool out = genericWriter(png_ptr, info_ptr, _inputImage);
	
	fileName.fileClose();
	return out;
}
