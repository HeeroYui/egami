/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
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
		int32_t biClrUsed;
		int32_t biClrImportant;
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
	EGAMI_DEBUG("        biClrUsed      =" << _info.biClrUsed << "      speglTexImage2Dcifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.");
	EGAMI_DEBUG("        biClrImportant =" << _info.biClrImportant << "      specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.");
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



egami::Image egami::loadBMP(const std::string& _inputFile) {
	egami::Image out;
	enum modeBitmap m_dataMode = BITS_16_R5G6B5;
	int32_t m_width = 0;
	int32_t m_height = 0;
	struct bitmapFileHeader m_FileHeader;
	struct bitmapInfoHeader m_InfoHeader;

	etk::FSNode fileName(_inputFile);
	// get the fileSize ...
	/*if (fileName.size() < (int32_t)(sizeof(struct bitmapFileHeader) + sizeof(struct bitmapFileHeader) ) ) {
		EGAMI_ERROR("not enought data in the file named=\"" << fileName << "\"");
		return;
	}*/
	if (fileName.exist() == false) {
		EGAMI_ERROR("File does not existed=\"" << fileName << "\"");
		return out;
	}
	if(fileName.fileOpenRead() ==false) {
		EGAMI_ERROR("Can not find the file name=\"" << fileName << "\"");
		return out;
	}
	// get the data : 
	if (fileName.fileRead(&m_FileHeader,sizeof(struct bitmapFileHeader),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return out;
	}
	if (fileName.fileRead(&m_InfoHeader,sizeof(struct bitmapInfoHeader),1) != 1) {
		EGAMI_ERROR("error loading file header");
		fileName.fileClose();
		return out;
	}
	//display(m_FileHeader, m_InfoHeader);
	//EGAMI_ERROR("plopppppppppppppp " << m_FileHeader.bfOffBits);
	if(fileName.fileSeek(m_FileHeader.bfOffBits, etk::seekNode_start) == false) {
		EGAMI_ERROR("error with the 'bfOffBits' in the file named=\"" << fileName << "\"");
		fileName.fileClose();
		return out;
	}
	// check the header error : 
	if (m_FileHeader.bfType != 0x4D42) {
		EGAMI_ERROR("the file=\"" << fileName << "\" is not a bitmap file ...");
		fileName.fileClose();
		return out;
	}
	if (m_FileHeader.bfReserved != 0x00000000) {
		EGAMI_ERROR("the bfReserved feald is not at 0  == > not supported format ...");
		fileName.fileClose();
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
		fileName.fileClose();;
		return out;
	}
	std::vector<uint8_t> m_data;
	if(m_InfoHeader.biSizeImage != 0) {
		m_data.resize(m_InfoHeader.biSizeImage, 0);
		if (fileName.fileRead(&m_data[0],m_InfoHeader.biSizeImage,1) != 1){
			EGAMI_CRITICAL("Can not read the file with the good size...");
		}
	}
	fileName.fileClose();
	
	etk::Color<> tmpColor(0,0,0,0);
	
	// need now to generate RGBA data ...
	switch(m_dataMode) {
		case BITS_16_R5G6B5: {
				uint16_t * pointer = (uint16_t*)(&m_data[0]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setR((uint8_t)((*pointer & 0xF800) >> 8));
						tmpColor.setG((uint8_t)((*pointer & 0x07E0) >> 3));
						tmpColor.setB((uint8_t)(*pointer << 3));
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,yyy), tmpColor);
						pointer++;
					}
				}
			}
			break;
		case BITS_16_X1R5G5B5: {
				uint16_t * pointer = (uint16_t*)(&m_data[0]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setR((int8_t)((*pointer & 0x7C00) >> 7));
						tmpColor.setG((int8_t)((*pointer & 0x03E0) >> 2));
						tmpColor.setB((int8_t)(*pointer << 3));
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,yyy), tmpColor);
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
				uint8_t * pointer = (&m_data[0]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setR(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setB(*pointer++);
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,yyy), tmpColor);
					}
					for(int32_t xxx=0; xxx<offset; xxx++) {
						pointer++;
					}
				}
			}
			break;
		case BITS_32_X8R8G8B8: {
				uint8_t * pointer = (&m_data[0]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						pointer++;
						tmpColor.setR(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setB(*pointer++);
						tmpColor.setA(0xFF);
						out.set(ivec2(xxx,yyy), tmpColor);
					}
				}
			}
			break;
		case BITS_32_A8R8G8B8: {
				uint8_t * pointer = (&m_data[0]);
				for(int32_t yyy=0; yyy<m_height; yyy++) {
					for(int32_t xxx=0; xxx<m_width; xxx++) {
						tmpColor.setR(*pointer++);
						tmpColor.setG(*pointer++);
						tmpColor.setB(*pointer++);
						tmpColor.setA(*pointer++);
						out.set(ivec2(xxx,yyy), tmpColor);
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

bool egami::storeBMP(const std::string& _fileName, const egami::Image& _inputImage) {
	struct bitmapFileHeader m_FileHeader;
	struct bitmapInfoHeader m_InfoHeader;
	
	m_FileHeader.bfType = 0x4D42;
	m_FileHeader.bfSize = sizeof(struct bitmapFileHeader);
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
	m_InfoHeader.biXPelsPerMeter = 75;
	m_InfoHeader.biYPelsPerMeter = 75;
	m_InfoHeader.biClrUsed = 0;
	m_InfoHeader.biClrImportant = 0;
	
	//display(m_FileHeader, m_InfoHeader);
	
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
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,yyy));
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
				const etk::Color<>& tmpColor = _inputImage.get(ivec2(xxx,yyy));
				uint8_t* pointer = data;
				*pointer++ = tmpColor.r();
				*pointer++ = tmpColor.g();
				*pointer++ = tmpColor.b();
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

