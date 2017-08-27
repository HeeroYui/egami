/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperJPG.hpp>
#include <etk/os/FSNode.hpp>
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


egami::Image egami::loadJPG(const etk::String& _inputFile) {
	etk::FSNode fileName(_inputFile);
	if (fileName.exist() == false) {
		EGAMI_ERROR("File does not existed='" << fileName << "'");
		return egami::Image();
	}
	if(fileName.fileOpenRead() == false) {
		EGAMI_ERROR("Can not find the file name='" << fileName << "'");
		return egami::Image();
	}
	etk::Vector<uint8_t> allData = fileName.fileReadAll<uint8_t>();
	fileName.fileClose();
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


