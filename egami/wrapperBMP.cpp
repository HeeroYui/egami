/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperBMP.hpp>
#include <etk/os/FSNode.hpp>
extern "C" {
	#pragma pack(push,1)
	struct bitmapFileHeader {
		int16_t bfType;
		int32_t bfSize;
		int32_t bfReserved;
		int32_t bfOffBits;
	};
	struct bitmapInfoHeader {
		int32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		int16_t biPlanes;
		int16_t biBitCount;
		int32_t biCompression;
		int32_t biSizeImage;
		int32_t biXPelsPerMeter;
		int32_t biYPelsPerMeter;
		int32_t biPaletteNumber;
		int32_t biImportantColor;
	};
	struct bitmapInfoHeaderExtended {
		int32_t biSize;
		int32_t biWidth;
		int32_t biHeight;
		int16_t biPlanes;
		int16_t biBitCount;
		int32_t biCompression;
		int32_t biSizeImage;
		int32_t biXPelsPerMeter;
		int32_t biYPelsPerMeter;
		// https://en.wikipedia.org/wiki/BMP_file_format / example 2
		int32_t biPaletteNumber;
		int32_t biImportantColor;
		int32_t biLCSColorSpace; // This is at this position, inspection of "gimp" output ...
		int32_t biBitMaskRed;
		int32_t biBitMaskGreen;
		int32_t biBitMaskBlue;
		int32_t biBitMaskAlpha;
		int32_t biUnused[12];
	};
	#pragma pack(pop)
}
enum modeBitmap {
	BITS_16_R5G6B5,
	BITS_16_X1R5G5B5,
	BITS_24_R8G8B8,
	BITS_32_X8R8G8B8,
	BITS_32_A8R8G8B8
};


static void display(struct bitmapFileHeader _header, struct bitmapInfoHeader _info) {
	EGAMI_DEBUG(" -----------------------------------------------------------");
	EGAMI_DEBUG("Display caracteristic of the bitmap : ");
	EGAMI_DEBUG("    Header of file :");
	EGAMI_DEBUG("        bfType    =" << _header.bfType << "      19778 : must always be set to 'BM' to declare that this is a .bmp-file.");
	EGAMI_DEBUG("        bfSize    =" << _header.bfSize << "      specifies the size of the file in bytes.");
	EGAMI_DEBUG("        bfReserved=" << _header.bfReserved << "      must always be set to zero.");
	EGAMI_DEBUG("        bfOffBits =" << _header.bfOffBits << "      1078 : specifies the offset from the beginning of the file to the bitmap data.");
	EGAMI_DEBUG("    info header of file :");
	EGAMI_DEBUG("        biSize         =" << _info.biSize << "      specifies the size of the BITMAPINFOHEADER structure, in bytes.");
	EGAMI_DEBUG("        biWidth        =" << _info.biWidth << "      specifies the width of the image, in pixels.");
	EGAMI_DEBUG("        biHeight       =" << _info.biHeight << "      specifies the height of the image, in pixels.");
	EGAMI_DEBUG("        biPlanes       =" << _info.biPlanes << "      specifies the number of planes of the target device, must be set to zero.");
	EGAMI_DEBUG("        biBitCount     =" << _info.biBitCount << "      specifies the number of bits per pixel.");
	EGAMI_DEBUG("        biCompression  =" << _info.biCompression << "      Specifies the type of compression, usually set to zero (no compression).");
	EGAMI_DEBUG("        biSizeImage    =" << _info.biSizeImage << "      specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.");
	EGAMI_DEBUG("        biXPelsPerMeter=" << _info.biXPelsPerMeter << "      specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.");
	EGAMI_DEBUG("        biYPelsPerMeter=" << _info.biYPelsPerMeter << "      specifies the the vertical pixels per meter on the designated targer device, usually set to zero.");
	EGAMI_DEBUG("        biClrUsed      =" << _info.biPaletteNumber << "      Pallet color number.");
	EGAMI_DEBUG("        biClrImportant =" << _info.biImportantColor << "      Important color ID.");
	/*
	EGAMI_DEBUG("Bitmap : " << m_width << "x" << m_height);
	switch(m_dataMode)
	{
		case BITS_16_R5G6B5:
			EGAMI_DEBUG("        mode = 16 bits R5G6B5");
			break;
		case BITS_16_X1R5G5B5:
			EGAMI_DEBUG("        mode = 16 bits X1R5G5B5");
			break;
		case BITS_24_R8G8B8:
			EGAMI_DEBUG("        mode = 24 bits R8G8B8");
			break;
		case BITS_32_X8R8G8B8:
			EGAMI_DEBUG("        mode = 32 bits X8R8G8B8");
			break;
		case BITS_32_A8R8G8B8:
			EGAMI_DEBUG("        mode = 32 bits A8R8G8B8");
			break;
		default:
			EGAMI_DEBUG("        mode = ERROR");
			break;
	}*/
}

egami::Image egami::loadBMP(const etk::String& _inputFile) {
	etk::FSNode fileName(_inputFile);
	EGAMI_VERBOSE("File='" << _inputFile << "' ==> " << fileName << " ==> " << fileName.getFileSystemName());
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
	return egami::loadBMP(allData);
}

egami::Image egami::loadBMP(const etk::Vector<uint8_t>& _buffer) {
	egami::Image out;
	enum modeBitmap m_dataMode = BITS_16_R5G6B5;
	int32_t m_width = 0;
	int32_t m_height = 0;
	struct bitmapFileHeader m_FileHeader;
	bool useExtended = false;
	struct bitmapInfoHeader m_InfoHeader;
	struct bitmapInfoHeaderExtended m_InfoHeaderExtended;
	if (_buffer.size() < sizeof(struct bitmapFileHeader)) {
		EGAMI_ERROR("error loading file header, not enough data");
		return out;
	}
	memcpy(&m_FileHeader, &_buffer[0], sizeof(struct bitmapFileHeader));
	// check the header error : 
	if (m_FileHeader.bfType != 0x4D42) {
		EGAMI_ERROR("the Buffer is not a bitmap file ... " << m_FileHeader.bfType << " != " << 0x4D42);
		return out;
	}
	if (m_FileHeader.bfOffBits > sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader)) {
		EGAMI_DEBUG("Read bitmap in EXTENDED mode ...");
		if (_buffer.size() < sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeaderExtended)) {
			EGAMI_ERROR("error loading file header, not enough data");
			return out;
		}
		memcpy(&m_InfoHeaderExtended, &_buffer[sizeof(struct bitmapFileHeader)], sizeof(struct bitmapInfoHeaderExtended));
		useExtended = true;
		m_InfoHeader.biSize = m_InfoHeaderExtended.biSize;
		m_InfoHeader.biWidth = m_InfoHeaderExtended.biWidth;
		m_InfoHeader.biHeight = m_InfoHeaderExtended.biHeight;
		m_InfoHeader.biHeight = m_InfoHeaderExtended.biHeight;
		m_InfoHeader.biHeight = m_InfoHeaderExtended.biHeight;
		m_InfoHeader.biBitCount = m_InfoHeaderExtended.biBitCount;
		m_InfoHeader.biCompression = m_InfoHeaderExtended.biCompression;
		m_InfoHeader.biSizeImage = m_InfoHeaderExtended.biSizeImage;
		m_InfoHeader.biXPelsPerMeter = m_InfoHeaderExtended.biXPelsPerMeter;
		m_InfoHeader.biYPelsPerMeter = m_InfoHeaderExtended.biYPelsPerMeter;
	} else {
		EGAMI_DEBUG("Read bitmap in BASIC mode ...");
		if (_buffer.size() < sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader)) {
			EGAMI_ERROR("error loading file header, not enough data");
			return out;
		}
		memcpy(&m_InfoHeader, &_buffer[sizeof(struct bitmapFileHeader)], sizeof(struct bitmapInfoHeader));
		useExtended = false;
	}
	int32_t offsetHeader = m_FileHeader.bfOffBits;
	display(m_FileHeader, m_InfoHeader);
	// check the header error : 
	if (m_FileHeader.bfType != 0x4D42) {
		EGAMI_ERROR("the Buffer is not a bitmap file ... " << m_FileHeader.bfType << " != " << 0x4D42);
		return out;
	}
	if (m_FileHeader.bfReserved != 0x00000000) {
		EGAMI_ERROR("the bfReserved feald is not at 0  == > not supported format ...");
		return out;
	}
	m_width = m_InfoHeader.biWidth;
	m_height = m_InfoHeader.biHeight;
	if(    m_InfoHeader.biBitCount == 16
	    && m_InfoHeader.biCompression == 0) {
		m_dataMode = BITS_16_X1R5G5B5;
		out.configure(ivec2(m_width,m_height), egami::colorType::RGB8);
	} else if(    m_InfoHeader.biBitCount == 16
	         && m_InfoHeader.biCompression == 3) {
		m_dataMode = BITS_16_R5G6B5;
		out.configure(ivec2(m_width,m_height), egami::colorType::RGB8);
	} else if(    m_InfoHeader.biBitCount == 24
	           && m_InfoHeader.biCompression == 0) {
		m_dataMode = BITS_24_R8G8B8;
		out.configure(ivec2(m_width,m_height), egami::colorType::RGB8);
	} else if(    m_InfoHeader.biBitCount == 32
	           && m_InfoHeader.biCompression == 3) {
		m_dataMode = BITS_32_X8R8G8B8;
		out.configure(ivec2(m_width,m_height), egami::colorType::RGB8);
	} else if(    m_InfoHeader.biBitCount == 32
	           && m_InfoHeader.biCompression == 0) {
		m_dataMode = BITS_32_A8R8G8B8;
		out.configure(ivec2(m_width,m_height), egami::colorType::RGBA8);
	} else {
		EGAMI_ERROR("the biBitCount & biCompression fealds are unknow  == > not supported format ...");
		return out;
	}

	if(m_InfoHeader.biSizeImage != 0) {
		if (_buffer.size() < offsetHeader + m_InfoHeader.biSizeImage) {
			EGAMI_CRITICAL("Can not read the file with the good size...");
		}
	}
	
	etk::Color<> tmpColor(0,0,0,0);
	
	// need now to generate RGBA data ...
	switch(m_dataMode) {
		case BITS_16_R5G6B5: {
				const uint16_t * pointer = (const uint16_t*)(&_buffer[offsetHeader]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setB((uint8_t)((*pointer & 0xF800) >> 8));
						tmpColor.setG((uint8_t)((*pointer & 0x07E0) >> 3));
						tmpColor.setR((uint8_t)(*pointer << 3));
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,m_height-yyy-1), tmpColor);
						pointer++;
					}
				}
			}
			break;
		case BITS_16_X1R5G5B5: {
				const uint16_t * pointer = (const uint16_t*)(&_buffer[offsetHeader]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setB((int8_t)((*pointer & 0x7C00) >> 7));
						tmpColor.setG((int8_t)((*pointer & 0x03E0) >> 2));
						tmpColor.setR((int8_t)(*pointer << 3));
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,m_height-yyy-1), tmpColor);
						pointer++;
					}
				}
			}
			break;
		case BITS_24_R8G8B8: {
				int32_t offset = 0;
				int32_t baseLine = m_width * 3;
				if ((baseLine%4) == 1) {
					offset = 3;
				} else if ((baseLine%4) == 2) {
					offset = 2;
				} else if ((baseLine%4) == 3) {
					offset = 1;
				}
				const uint8_t * pointer = (&_buffer[offsetHeader]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setB(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setR(*pointer++);
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,m_height-yyy-1), tmpColor);
					}
					for(int32_t xxx=0; xxx<offset; xxx++) {
						pointer++;
					}
				}
			}
			break;
		case BITS_32_X8R8G8B8: {
				const uint8_t * pointer = (&_buffer[offsetHeader]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						pointer++;
						tmpColor.setB(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setR(*pointer++);
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,m_height-yyy-1), tmpColor);
					}
				}
			}
			break;
		case BITS_32_A8R8G8B8: {
				const uint8_t * pointer = (&_buffer[offsetHeader]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setB(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setR(*pointer++);
						tmpColor.setA(*pointer++);
						out.set(ivec2(xxx,m_height-yyy-1), tmpColor);
					}
				}
			}
			break;
		default:
			EGAMI_ERROR("        mode = ERROR");
			break;
	}
	return out;
}

#if 1
	// Extended mode
bool egami::storeBMP(const etk::String& _fileName, const egami::Image& _inputImage) {
	struct bitmapFileHeader m_FileHeader;
	struct bitmapInfoHeaderExtended m_InfoHeaderExtended;
	memset(&m_InfoHeaderExtended, 0, sizeof(bitmapInfoHeaderExtended));
	m_FileHeader.bfType = 0x4D42;
	m_FileHeader.bfSize = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeaderExtended);
	m_FileHeader.bfReserved = 0;
	m_FileHeader.bfOffBits = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeaderExtended);
	//EGAMI_ERROR("plopppppppppppppp " << m_FileHeader.bfOffBits);
	m_InfoHeaderExtended.biSize = sizeof(struct bitmapInfoHeaderExtended);
	m_InfoHeaderExtended.biWidth = _inputImage.getSize().x();
	m_InfoHeaderExtended.biHeight = _inputImage.getSize().y();
	m_InfoHeaderExtended.biPlanes = 1;
	int32_t offset = 0;
	if (_inputImage.getType() == egami::colorType::RGBA8) {
		m_InfoHeaderExtended.biBitCount = 32;
		m_InfoHeaderExtended.biCompression = 0;
		m_InfoHeaderExtended.biSizeImage = _inputImage.getSize().x()*_inputImage.getSize().y()*4;
	} else {
		m_InfoHeaderExtended.biBitCount = 24;
		m_InfoHeaderExtended.biCompression = 0;
		int32_t baseLine = _inputImage.getSize().x() * 3;
		if ((baseLine%4) == 1) {
			offset = 3;
		} else if ((baseLine%4) == 2) {
			offset = 2;
		} else if ((baseLine%4) == 3) {
			offset = 1;
		}
		m_InfoHeaderExtended.biSizeImage = (baseLine+offset)*_inputImage.getSize().y();
	}
	m_FileHeader.bfSize += m_InfoHeaderExtended.biSizeImage;
	m_InfoHeaderExtended.biXPelsPerMeter = 72*39.3701+1;
	m_InfoHeaderExtended.biYPelsPerMeter = 72*39.3701+1;
	//m_InfoHeaderExtended.biClrUsed = 0;
	//m_InfoHeaderExtended.biClrImportant = 0;
	
	m_InfoHeaderExtended.biLCSColorSpace = 0x73524742; // "Win "
	
	//display(m_FileHeader, m_InfoHeaderExtended);
	m_InfoHeaderExtended.biBitMaskRed   = 0x0000FF00;
	m_InfoHeaderExtended.biBitMaskGreen = 0x00FF0000;
	m_InfoHeaderExtended.biBitMaskBlue  = 0xFF000000;
	m_InfoHeaderExtended.biBitMaskAlpha = 0x000000FF;
	
	etk::FSNode fileName(_fileName);
	if(false == fileName.fileOpenWrite() ) {
		EGAMI_ERROR("Can not find the file name=\"" << fileName << "\"");
		return false;
	}
	// Write header:
	if (fileName.fileWrite(&m_FileHeader,sizeof(struct bitmapFileHeader),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return false;
	}
	if (fileName.fileWrite(&m_InfoHeaderExtended,sizeof(struct bitmapInfoHeaderExtended),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return false;
	}
	
	/* TODO: Avec ca, ca ne fonctionne pas ... ==> check
	if(fileName.fileSeek(m_FileHeader.bfOffBits, etk::FSN_SEEK_START) == false) {
		EGAMI_ERROR("error with the 'bfOffBits' in the file named=\"" << fileName << "\"");
		fileName.fileClose();
		return false;
	}
	*/
	if (_inputImage.getType() == egami::colorType::RGBA8) {
		uint8_t data[16];
		for(int32_t yyy=0; yyy<_inputImage.getSize().y(); ++yyy) {
			for(int32_t xxx=0; xxx<_inputImage.getSize().x(); ++xxx) {
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,_inputImage.getSize().y()-yyy-1));
				uint8_t* pointer = data;
				*pointer++ = tmpColor.r();
				*pointer++ = tmpColor.g();
				*pointer++ = tmpColor.b();
				*pointer++ = tmpColor.a();
				fileName.fileWrite(data,4,1);
			}
		}
	} else {
		uint8_t data[16];
		for(int32_t yyy=0; yyy<_inputImage.getSize().y(); ++yyy) {
			for(int32_t xxx=0; xxx<_inputImage.getSize().x(); ++xxx) {
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,_inputImage.getSize().y()-yyy-1));
				uint8_t* pointer = data;
				*pointer++ = tmpColor.b();
				*pointer++ = tmpColor.g();
				*pointer++ = tmpColor.r();
				fileName.fileWrite(data,3,1);
			}
			if (offset != 0) {
				uint8_t pointer[4];
				pointer[0] = 0;
				pointer[1] = 0;
				pointer[2] = 0;
				pointer[3] = 0;
				fileName.fileWrite(pointer,1,offset);
			}
		}
	}
	fileName.fileClose();
	return true;
}
#else
// old mode:
bool egami::storeBMP(const etk::String& _fileName, const egami::Image& _inputImage) {
	struct bitmapFileHeader m_FileHeader;
	struct bitmapInfoHeader m_InfoHeader;
	memset(&m_InfoHeader, 0, sizeof(bitmapInfoHeader));
	m_FileHeader.bfType = 0x4D42;
	m_FileHeader.bfSize = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader);
	m_FileHeader.bfReserved = 0;
	m_FileHeader.bfOffBits = sizeof(struct bitmapFileHeader) + sizeof(struct bitmapInfoHeader);
	//EGAMI_ERROR("plopppppppppppppp " << m_FileHeader.bfOffBits);
	m_InfoHeader.biSize = sizeof(struct bitmapInfoHeader);
	m_InfoHeader.biWidth = _inputImage.getSize().x();
	m_InfoHeader.biHeight = _inputImage.getSize().y();
	m_InfoHeader.biPlanes = 1;
	int32_t offset = 0;
	if (_inputImage.getType() == egami::colorType::RGBA8) {
		m_InfoHeader.biBitCount = 32;
		m_InfoHeader.biCompression = 0;
		m_InfoHeader.biSizeImage = _inputImage.getSize().x()*_inputImage.getSize().y()*4;
	} else {
		m_InfoHeader.biBitCount = 24;
		m_InfoHeader.biCompression = 0;
		int32_t baseLine = _inputImage.getSize().x() * 3;
		if ((baseLine%4) == 1) {
			offset = 3;
		} else if ((baseLine%4) == 2) {
			offset = 2;
		} else if ((baseLine%4) == 3) {
			offset = 1;
		}
		m_InfoHeader.biSizeImage = (baseLine+offset)*_inputImage.getSize().y();
	}
	m_FileHeader.bfSize += m_InfoHeader.biSizeImage;
	m_InfoHeader.biXPelsPerMeter = 72*39.3701+1;
	m_InfoHeader.biYPelsPerMeter = 72*39.3701+1;
	//m_InfoHeader.biClrUsed = 0;
	//m_InfoHeader.biClrImportant = 0;
	
	
	etk::FSNode fileName(_fileName);
	if(false == fileName.fileOpenWrite() ) {
		EGAMI_ERROR("Can not find the file name=\"" << fileName << "\"");
		return false;
	}
	// Write header:
	if (fileName.fileWrite(&m_FileHeader,sizeof(struct bitmapFileHeader),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return false;
	}
	if (fileName.fileWrite(&m_InfoHeader,sizeof(struct bitmapInfoHeader),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return false;
	}
	EGAMI_ERROR("header size = " << sizeof(struct bitmapFileHeader) << " + " << sizeof(struct bitmapInfoHeader) << " = " << (sizeof(struct bitmapFileHeader)+sizeof(struct bitmapInfoHeader)) );
	
	/* TODO: Avec ca, ca ne fonctionne pas ... ==> check
	if(fileName.fileSeek(m_FileHeader.bfOffBits, etk::FSN_SEEK_START) == false) {
		EGAMI_ERROR("error with the 'bfOffBits' in the file named=\"" << fileName << "\"");
		fileName.fileClose();
		return false;
	}
	*/
	if (_inputImage.getType() == egami::colorType::RGBA8) {
		uint8_t data[16];
		for(int32_t yyy=0; yyy<_inputImage.getSize().y(); ++yyy) {
			for(int32_t xxx=0; xxx<_inputImage.getSize().x(); ++xxx) {
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,_inputImage.getSize().y()-yyy-1));
				uint8_t* pointer = data;
				*pointer++ = tmpColor.r();
				*pointer++ = tmpColor.g();
				*pointer++ = tmpColor.b();
				*pointer++ = tmpColor.a();
				fileName.fileWrite(data,4,1);
			}
		}
	} else {
		uint8_t data[16];
		for(int32_t yyy=0; yyy<_inputImage.getSize().y(); ++yyy) {
			for(int32_t xxx=0; xxx<_inputImage.getSize().x(); ++xxx) {
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,_inputImage.getSize().y()-yyy-1));
				uint8_t* pointer = data;
				*pointer++ = tmpColor.b();
				*pointer++ = tmpColor.g();
				*pointer++ = tmpColor.r();
				fileName.fileWrite(data,3,1);
			}
			if (offset != 0) {
				uint8_t pointer[4];
				pointer[0] = 0;
				pointer[1] = 0;
				pointer[2] = 0;
				pointer[3] = 0;
				fileName.fileWrite(pointer,1,offset);
			}
		}
	}
	fileName.fileClose();
	return true;
}
#endif

