/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperJPG.hpp>
#include <etk/uri/uri.hpp>
extern "C" {
	#include "jpeglib.h"
}
#include <setjmp.h>

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */
	jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */
METHODDEF(void) my_error_exit(j_common_ptr _cinfo) {
	// cinfo->err really points to a my_error_mgr struct, so coerce pointer 
	my_error_ptr myerr = (my_error_ptr)_cinfo->err;
	// Always display the message.
	// We could postpone this until after returning, if we chose.
	(*_cinfo->err->output_message)(_cinfo);
	// Return control to the setjmp point
	longjmp(myerr->setjmp_buffer, 1);
}

void put_scanline_someplace(const uint8_t* _buffer, int32_t _row_stride) {
	EGAMI_ERROR("plop " << uint64_t(_buffer) << "  row=" << _row_stride << "  " << (_row_stride/3));
}


egami::Image egami::loadJPG(const etk::Uri& _uri) {
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EGAMI_ERROR("Can not create the uri: " << _uri);
		return egami::Image();
	}
	if (fileIo->open(etk::io::OpenMode::Read) == false) {
		EGAMI_ERROR("Can not open (r) the file : " << _uri);
		return egami::Image();
	}
	etk::Vector<uint8_t> allData = fileIo->readAll<uint8_t>();
	fileIo->close();
	return egami::loadJPG(allData);
}

egami::Image egami::loadJPG(const etk::Vector<uint8_t>& _buffer) {
	egami::Image out;
	// This struct contains the JPEG decompression parameters and pointers to working space (which is allocated as needed by the JPEG library).
	struct jpeg_decompress_struct cinfo;
	// We use our private extension JPEG error handler. Note that this struct must live as long as the main JPEG parameter struct, to avoid dangling-pointer problems.
	struct my_error_mgr jerr;
	// More stuff
	JSAMPARRAY buffer;
	int row_stride;
	
	// Step 1: allocate and initialize JPEG decompression object
	
	// We set up the normal JPEG error routines, then override error_exit.
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	// Establish the setjmp return context for my_error_exit to use.
	if (setjmp(jerr.setjmp_buffer)) {
		// If we get here, the JPEG code has signaled an error. We need to clean up the JPEG object, close the input file, and return.
		jpeg_destroy_decompress(&cinfo);
		return out;
	}
	// Now we can initialize the JPEG decompression object.
	jpeg_create_decompress(&cinfo);
	
	// Step 2: specify data source (eg, a file)
	jpeg_mem_src(&cinfo, &_buffer[0], _buffer.size());
	
	// Step 3: read file parameters with jpeg_read_header()
	(void)jpeg_read_header(&cinfo, TRUE);
	// We can ignore the return value from jpeg_read_header since
	//     (a) suspension is not possible with the stdio data source, and
	//     (b) we passed TRUE to reject a tables-only JPEG file as an error.
	// See libjpeg.txt for more info.
	
	// Step 4: set parameters for decompression
	// In this example, we don't need to change any of the defaults set by jpeg_read_header(), so we do nothing here.
	
	// Step 5: Start decompressor
	(void) jpeg_start_decompress(&cinfo);
	// We can ignore the return value since suspension is not possible with the stdio data source.
	
	// We may need to do some setup of our own at this point before reading the data.
	// After jpeg_start_decompress() we have the correct scaled output image dimensions available, as well as the output colormap if we asked for color quantization.
	// In this example, we need to make an output work buffer of the right size.
	// JSAMPLEs per row in output buffer
	row_stride = cinfo.output_width * cinfo.output_components;
	// Make a one-row-high sample array that will go away when done with image
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	
	// Step 6: while (scan lines remain to be read) jpeg_read_scanlines(...);
	// Resize output image:
	out.configure(ivec2(cinfo.output_width,cinfo.output_height), egami::colorType::RGB8);
	uint8_t* dataOutPointer = (uint8_t*)out.getTextureDataPointer();
	
	
	// Here we use the library's state variable cinfo.output_scanline as the loop counter, so that we don't have to keep track ourselves.
	int32_t yyy = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		// Get a simple line:
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		// Direst push on the output (got output format RGB8)
		//uint8_t* tmpp = dataOutPointer + (row_stride*(cinfo.output_height-yyy));
		uint8_t* tmpp = dataOutPointer + (row_stride*yyy);
		memcpy(tmpp, buffer[0], row_stride);
		yyy++;
	}
	// Step 7: Finish decompression
	(void) jpeg_finish_decompress(&cinfo);
	// We can ignore the return value since suspension is not possible with the stdio data source.
	
	// Step 8: Release JPEG decompression object
	// This is an important step since it will release a good deal of memory.
	jpeg_destroy_decompress(&cinfo);
	
	// At this point you may want to check to see whether any corrupt-data warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	return out;
}

static etk::Vector<JOCTET> myBuffer;
#define BLOCK_SIZE 16384

void myInitDestination(j_compress_ptr _cinfo) {
		myBuffer.resize(BLOCK_SIZE);
		_cinfo->dest->next_output_byte = &myBuffer[0];
		_cinfo->dest->free_in_buffer = myBuffer.size();
}

boolean myEmptyOutputBuffer(j_compress_ptr _cinfo) {
		size_t oldsize = myBuffer.size();
		myBuffer.resize(oldsize + BLOCK_SIZE);
		_cinfo->dest->next_output_byte = &myBuffer[oldsize];
		_cinfo->dest->free_in_buffer = myBuffer.size() - oldsize;
		return TRUE;
}

void myTermDestination(j_compress_ptr _cinfo) {
		myBuffer.resize(myBuffer.size() - _cinfo->dest->free_in_buffer);
}

bool egami::storeJPG(const etk::Uri& _uri, const egami::Image& _inputImage) {
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EGAMI_ERROR("Can not create the uri: " << _uri);
		return false;
	}
	if (fileIo->open(etk::io::OpenMode::Write) == false) {
		EGAMI_ERROR("Can not open (w) the file : " << _uri);
		return false;
	}
	etk::Vector<uint8_t> allData;
	bool ret = storeJPG(allData, _inputImage);
	fileIo->writeAll(allData);
	fileIo->close();
	return ret;
}

/*
 * IMAGE DATA FORMATS:
 *
 * The standard input image format is a rectangular array of pixels, with
 * each pixel having the same number of "component" values (color channels).
 * Each pixel row is an array of JSAMPLEs (which typically are unsigned chars).
 * If you are working with color data, then the color values for each pixel
 * must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
 * RGB color.
 *
 * For this example, we'll assume that this data structure matches the way
 * our application has stored the image in memory, so we can just pass a
 * pointer to our image buffer.	In particular, let's say that the image is
 * RGB color and is described by:
 */

//int quality = 250;
int quality = 200;

bool egami::storeJPG(etk::Vector<uint8_t>& _buffer, const egami::Image& _inputImage) {
	_buffer.clear();
	/* This struct contains the JPEG compression parameters and pointers to
	 * working space (which is allocated as needed by the JPEG library).
	 * It is possible to have several such structures, representing multiple
	 * compression/decompression processes, in existence at once.	We refer
	 * to any one struct (and its associated working data) as a "JPEG object".
	 */
	struct jpeg_compress_struct cinfo;
	// We use our private extension JPEG error handler. Note that this struct must live as long as the main JPEG parameter struct, to avoid dangling-pointer problems.
	struct my_error_mgr jerr;
	/* More stuff */
	int row_stride; /* physical row width in image buffer */

	/* Step 1: allocate and initialize JPEG compression object */

	// We set up the normal JPEG error routines, then override error_exit.
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	/* Now we can initialize the JPEG compression object. */
	jpeg_create_compress(&cinfo);

	/* Step 2: specify data destination (eg, a file) */
	/* Note: steps 2 and 3 can be done in either order. */

	/* Here we use the library-supplied code to send compressed data to a
	 * stdio stream.	You can also write your own code to do something else.
	 * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	 * requires it in order to write binary files.
	 */
	#if 0
		FILE * outfile; /* target file */
		if ((outfile = fopen(filename, "wb")) == NULL) {
			fprintf(stderr, "can't open %s\n", filename);
			exit(1);
		}
		jpeg_stdio_dest(&cinfo, outfile);
	#else
		/*
		uint8_t* rgba = null;
		unsigned long size = 0;
		etk::Vector<uint8_t> buffer.
		jpeg_mem_dest(jpegdata, &rgba, &size);
		if(size > 0) {
			buffer.resize(size);
			for(ii=0; iii<size; ++iii) {
				buffer[iii] = rgba[iii];
			}
			free(rgba);
			rgba = null;
		}
		*/
		jpeg_stdio_dest(&cinfo, null);
		if (cinfo.dest == null) {
			EGAMI_ERROR("Can not write the destination property callback");
			return false;
		}
		cinfo.dest->init_destination = &myInitDestination;
		cinfo.dest->empty_output_buffer = &myEmptyOutputBuffer;
		cinfo.dest->term_destination = &myTermDestination;
	#endif

	// Step 3: set parameters for compression
	// First we supply a description of the input image. Four fields of the cinfo struct must be filled in:
	cinfo.image_width = _inputImage.getSize().x();
	cinfo.image_height = _inputImage.getSize().y();
	// # of color components per pixel
	cinfo.input_components = getFormatColorSize(_inputImage.getType());
	// colorspace of input image
	cinfo.in_color_space = JCS_RGB;
	/* Now use the library's routine to set default compression parameters.
	 * (You must set at least cinfo.in_color_space before calling this,
	 * since the defaults depend on the source color space.)
	 */
	jpeg_set_defaults(&cinfo);
	/* Now you can set any non-default parameters you wish to.
	 * Here we just illustrate the use of quality (quantization table) scaling:
	 */
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

	/* Step 4: Start compressor */

	/* TRUE ensures that we will write a complete interchange-JPEG file.
	 * Pass TRUE unless you are very sure of what you're doing.
	 */
	jpeg_start_compress(&cinfo, TRUE);

	/* Step 5: while (scan lines remain to be written) */
	/*					 jpeg_write_scanlines(...); */
	uint8_t * dataPointer = (uint8_t*)_inputImage.getTextureDataPointer();
	while (cinfo.next_scanline < cinfo.image_height) {
		/* jpeg_write_scanlines expects an array of pointers to scanlines.
		 * Here the array is only one element long, but you could pass
		 * more than one scanline at a time if that's more convenient.
		 */
		JSAMPROW tmp[1];
		tmp[0] = &dataPointer[cinfo.next_scanline * cinfo.image_width * getFormatColorSize(_inputImage.getType())];
		(void) jpeg_write_scanlines(&cinfo, tmp, 1);
	}

	/* Step 6: Finish compression */

	jpeg_finish_compress(&cinfo);
	/* Step 7: release JPEG compression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_compress(&cinfo);
	etk::swap(_buffer, myBuffer);
	return true;
}
