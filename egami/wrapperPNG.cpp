/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperPNG.hpp>
#include <etk/os/FSNode.hpp>
#include <png/png.h>

// we must change the access of the IO of the png lib :
static void local_ReadData(png_structp png_ptr, png_bytep data, png_size_t length) {
	etk::FSNode* fileNode = static_cast<etk::FSNode*>(png_get_io_ptr(png_ptr));
	if (fileNode != nullptr) {
		fileNode->fileRead(data, 1, length);
	}
}
/*
static void LocalWriteData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	etk::FSNode* fileNode = static_cast<etk::FSNode*>(png_get_io_ptr(png_ptr));
	if (NULL!=fileNode) {
		fileNode->FileWrite(data, 1, length);
	}
}

static void localFlushData(png_structp png_ptr)
{
	etk::FSNode* fileNode = static_cast<etk::FSNode*>(png_get_io_ptr(png_ptr));
	if (NULL!=fileNode) {
		fileNode->FileFlush();
	}
}
*/

void user_error_fn(png_structp _pngPtr, png_const_charp _errorMsg) {
	EGAMI_ERROR("libpng error: '" << _errorMsg << "'");
}

void user_warning_fn(png_structp _pngPtr, png_const_charp _warningMsg) {
	EGAMI_WARNING("libpng warning: '" << _warningMsg << "'");
}

egami::Image egami::loadPNG(const std::string& _inputFile) {
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
	png_infop info_ptr;
	png_structp png_ptr;
	
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
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, user_error_fn, user_warning_fn);
	if (png_ptr == nullptr) {
		EGAMI_ERROR("Can not Allocate PNG structure");
		fileName.fileClose();
		return out;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		EGAMI_ERROR("Can not Allocate PNG info structure");
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		fileName.fileClose();
		return out;
	}
	/*
	if (setjmp(png_jmpbuf(png_ptr))) {
		EGAMI_ERROR(" Can not set the JUMP buffer adresses");
		// Free all of the memory associated with the png_ptr and info_ptr
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fileName.fileClose();
		return false;
	}
	*/
	// overwrite the read and write function :
	png_set_read_fn(png_ptr,
	                &fileName,
	                &local_ReadData);
	/*
	png_set_write_fn(png_ptr,
	                 &fileName,
	                 &LocalWriteData,
	                 &localFlushData);
	*/
	// If we have already read some of the signature
	png_set_sig_bytes(png_ptr, 8);
	
	png_read_info(png_ptr, info_ptr);
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bit_depth = 0;
	int colorType = 0;
	int interlace_type = 0;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &colorType, &interlace_type, nullptr, nullptr);
	// reallocate the image 
	EGAMI_VERBOSE("Load PNG image : (" << width << "," << height << ")" );
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
		png_set_scale_16(png_ptr);
	#else
		png_set_strip_16(png_ptr);
	#endif
	
	// Strip alpha bytes from the input data without combining with the background (not recommended).
	//png_set_strip_alpha(png_ptr);
	
	// Extract multiple pixels with bit depths of 1, 2, and 4 from a single byte into separate bytes (useful for paletted and grayscale images).
	png_set_packing(png_ptr);
	
	// Change the order of packed pixels to least significant bit first (not useful if you are using png_set_packing).
	png_set_packswap(png_ptr);
	
	/* Expand paletted colors into true RGB triplets */
	if (colorType == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
	
	// Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel
	if (    colorType == PNG_COLOR_TYPE_GRAY
	     && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	
	// Expand paletted or RGB images with transparency to full alpha channels so the data will be available as RGBA quartets.
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) != 0) {
		png_set_tRNS_to_alpha(png_ptr);
	}
	
	/* Set the background color to draw transparent and alpha images over.
	 * It is possible to set the red, green, and blue components directly
	 * for paletted images instead of supplying a palette index.  Note that
	 * even if the PNG file supplies a background, you are not required to
	 * use it - you should use the (solid) application background if it has one.
	 */
	 /*
	png_color::16 my_background, *image_background;
	if (png_get_bKGD(png_ptr, info_ptr, &image_background) != 0) {
		png_set_background(png_ptr, image_background, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
	} else {
		png_set_background(png_ptr, &my_background, PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
	}
	*/
	/* Optional call to gamma correct and add the background to the palette
	 * and update info structure.  REQUIRED if you are expecting libpng to
	 * update the palette for you (ie you selected such a transform above).
	 */
	png_read_update_info(png_ptr, info_ptr);
	
	// Allocate the memory to hold the image using the fields of info_ptr.
	// The easiest way to read the image:
	png_bytep row_pointers[height];
	/* Clear the pointer array */
	for (png_uint_32 row = 0; row < height; row++) {
		row_pointers[row] = nullptr;
	}
	for (png_uint_32 row = 0; row < height; row++) {
		row_pointers[row] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
	}
	EGAMI_DEBUG("Load image: " << _inputFile);
	png_read_image(png_ptr, row_pointers);
	EGAMI_DEBUG("Load image: " << _inputFile << " DONE");
	// Read rest of file, and get additional chunks in info_ptr - REQUIRED
	png_read_end(png_ptr, info_ptr);
	
	//png_set_expand(png_ptr);

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
			EGAMI_ERROR("Must be RGB+alpha?/GRAY+alpha? not supported : " << (int64_t)png_get_color_type(png_ptr, info_ptr));
			if ((png_get_color_type(png_ptr, info_ptr) & PNG_COLOR_MASK_PALETTE) != 0) {
				EGAMI_ERROR("    palette");
			}
			if ((png_get_color_type(png_ptr, info_ptr) & PNG_COLOR_MASK_COLOR) != 0) {
				EGAMI_ERROR("    color");
			}
			if ((png_get_color_type(png_ptr, info_ptr) & PNG_COLOR_MASK_ALPHA) != 0) {
				EGAMI_ERROR("    Alpha");
			}
			return egami::Image();
	}
	fileName.fileClose();
	// Clean up after the read, and free any memory allocated - REQUIRED
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	return out;
}

