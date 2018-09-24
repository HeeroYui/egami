/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <egami/egami.hpp>
#include <egami/debug.hpp>

#ifdef EGAMI_BUILD_ESVG
	#include <egami/wrapperSVG.hpp>
#endif
#ifdef EGAMI_BUILD_PNG
	#include <egami/wrapperPNG.hpp>
#endif
#include <egami/wrapperBMP.hpp>
#include <egami/wrapperEDF.hpp>

#ifdef EGAMI_BUILD_JPEG
	#include <egami/wrapperJPG.hpp>
#endif
#ifdef EGAMI_BUILD_JPEG2000
	#include <egami/wrapperJPG2000.hpp>
#endif
#ifdef EGAMI_BUILD_TIFF
	#include <egami/wrapperTIFF.hpp>
#endif
#include <edtaa3/edtaa3func.h>

bool egami::scalable(const etk::Uri& _uri) {
	if (etk::toLower(_uri.getPath().getExtention()) == "svg") {
		return true;
	}
	return false;
}

egami::Image egami::load(const etk::Uri& _uri, const ivec2& _size) {
	etk::String extention = etk::toLower(_uri.getPath().getExtention());
	egami::Image out;
	// select the corect Loader :
	if (extention == "edf") {
		// internal format for ewol distance field ==> simple sistance field image
		out = egami::loadEDF(_uri);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load EDF file '" << _uri << "'");
		}
	} else if (extention == "bmp") {
		out = egami::loadBMP(_uri);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load BMP file '" << _uri << "'");
		}
	} else if (extention == "svg") {
		#ifdef EGAMI_BUILD_ESVG
			out = egami::loadSVG(_uri, _size);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load SVG file '" << _uri << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the ESVG dependency for file '" << _uri << "'");
		#endif
	} else if (extention == "png") {
		#ifdef EGAMI_BUILD_PNG
			out = egami::loadPNG(_uri);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load PNG file '" << _uri << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the PNG dependency for file '" << _uri << "'");
		#endif
	} else if (extention == "jpg") {
		#ifdef EGAMI_BUILD_JPEG
			out = egami::loadJPG(_uri);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load JPG file '" << _uri << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the JPEG dependency for file '" << _uri << "'");
		#endif
	} else if (extention == "j2k") {
		#ifdef EGAMI_BUILD_JPEG2000
			out = egami::loadJPG2000(_uri);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load JPEG2000 file '" << _uri << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the JPEG 2000 (openjpeg) dependency for file '" << _uri << "'");
		#endif
	} else if (extention == "tif") {
		#ifdef EGAMI_BUILD_TIFF
			out = egami::loadTIFF(_uri);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load TIFF file '" << _uri << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the TIFF dependency for file '" << _uri << "'");
		#endif
	} else {
		EGAMI_ERROR("Extention not managed '" << _uri << "' Sopported extention : .edf / .bmp / .svg / .png / .jpg / .j2k / .tif");
	}
	return out;
}


egami::Image egami::load(const etk::String& _mineType, const etk::Vector<uint8_t>& _buffer, const ivec2& _size) {
	egami::Image out;
	// select the corect Loader :
	if (_mineType == "image/bmp") {
		out = egami::loadBMP(_buffer);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load BMP file '" << _buffer.size() << "'");
		}
	}else if (_mineType == "image/png") {
		#ifdef EGAMI_BUILD_PNG
			out = egami::loadPNG(_buffer);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load PNG file '" << _buffer.size() << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the PNG dependency for file '" << _buffer.size() << "'");
		#endif
	} else if (_mineType == "image/jpeg") {
		#ifdef EGAMI_BUILD_JPEG
			out = egami::loadJPG(_buffer);
			if (out.exist() == false) {
				EGAMI_ERROR("Error to load JPG file '" << _buffer.size() << "'");
			}
		#else
			EGAMI_WARNING("egami not compile with the JPEG dependency for file '" << _buffer.size() << "'");
		#endif
	} else {
		EGAMI_ERROR("Extention not managed '" << _mineType << "' Sopported extention : image/bmp, image/png, image/jpg");
	}
	return out;
}

bool egami::store(const egami::Image& _input, const etk::Uri& _uri) {
	etk::String extention = etk::toLower(_uri.getPath().getExtention());
	EGAMI_DEBUG("Store file : " << _uri);
	// select the corect Loader :
	if (extention == "edf") {
		if (egami::storeEDF(_uri, _input) == false) {
			EGAMI_ERROR("Error to store EDF file '" << _uri << "'");
			return false;
		}
	} else if (extention == "bmp") {
		if (egami::storeBMP(_uri, _input) == false) {
			EGAMI_ERROR("Error to store BMP file '" << _uri << "'");
			return false;
		}
	} else if (extention == "svg") {
		EGAMI_ERROR("Can not store in SVG file '" << _uri << "'");
		return false;
	} else if (extention == "png") {
		#ifdef EGAMI_BUILD_PNG
			if (egami::storePNG(_uri, _input) == false) {
				EGAMI_ERROR("Error to store PNG file '" << _uri << "'");
				return false;
			}
		#else
			EGAMI_WARNING("egami not compile with the PNG dependency for file '" << _uri << "'");
			return false;
		#endif
	} else if (extention == "jpg") {
		#ifdef EGAMI_BUILD_JPEG
			if (egami::storeJPG(_uri, _input) == false) {
				EGAMI_ERROR("Error to store JPEG file '" << _uri << "'");
				return false;
			}
		#else
			EGAMI_WARNING("egami not compile with the JPEG dependency for file '" << _uri << "'");
			return false;
		#endif
	} else if (extention == "j2k") {
		EGAMI_ERROR("Can not store in JPEG 2000 file '" << _uri << "'");
		return false;
	} else if (extention == "tif") {
		EGAMI_ERROR("Can not store in TIFF file '" << _uri << "'");
		return false;
	} else {
		EGAMI_ERROR("Extention not managed '" << _uri << "' Sopported extention: .edf / .bmp / .svg / .png / .jpg / .j2k / .tif");
		return false;
	}
	return true;
}
bool egami::store(const egami::Image& _input, etk::Vector<uint8_t>& _buffer, const etk::String& _mineType) {
	// clear output data.
	_buffer.clear();
	// select the corect Loader :
	if (_mineType == "image/bmp") {
		if (egami::storeBMP(_buffer, _input) == false) {
			EGAMI_ERROR("Error to store BMP for Raw output");
			return false;
		}
	}else if (_mineType == "image/png") {
		#ifdef EGAMI_BUILD_PNG
			if (egami::storePNG(_buffer, _input) == false) {
				EGAMI_ERROR("Error to store PNG for Raw output");
				return false;
			}
		#else
			EGAMI_WARNING("egami not compile with the PNG dependency for Raw output");
			return false;
		#endif
	} else if (_mineType == "image/jpeg") {
		#ifdef EGAMI_BUILD_JPEG
			if (egami::storeJPG(_buffer, _input) == false) {
				EGAMI_ERROR("Error to store JPG for Raw output");
				return false;
			}
		#else
			EGAMI_WARNING("egami not compile with the JPG dependency for Raw output");
			return false;
		#endif
		return false;
	} else {
		EGAMI_ERROR("Extention not managed  for Raw output Sopported extention: .bmp / .png / .jpg");
		return false;
	}
	return true;
}


static void generateDistanceField(const egami::ImageMono& _input, egami::Image& _output) {
	int32_t size = _input.getSize().x() * _input.getSize().y();
	etk::Vector<short> xdist(size);
	etk::Vector<short> ydist(size);
	etk::Vector<double> gx(size);
	etk::Vector<double> gy(size);
	etk::Vector<double> data(size);
	etk::Vector<double> outside(size);
	etk::Vector<double> inside(size);
	/*
	// Convert img into double (data)
	double img_min = 255, img_max = -255;
	for (int32_t yyy = 0; yyy < _input.getSize().y(); ++yyy) {
		for (int32_t xxx = 0; xxx < _input.getSize().x(); ++xxx) {
			int32_t iii = yyy * _input.getSize().x() + xxx;
			double v = _input.get(ivec2(xxx, yyy));
			data[iii] = v;
			if (v > img_max) {
				img_max = v;
			}
			if (v < img_min) {
				img_min = v;
			}
		}
	}
	// Rescale image levels between 0 and 1
	for (int32_t yyy = 0; yyy < _input.getSize().y(); ++yyy) {
		for (int32_t xxx = 0; xxx < _input.getSize().x(); ++xxx) {
			int32_t iii = yyy * _input.getSize().x() + xxx;
			data[iii] = (_input.get(ivec2(xxx, yyy))-img_min)/img_max;
		}
	}
	
	// Compute outside = edtaa3(bitmap); % Transform background (0's)
	computegradient(&data[0], _input.getSize().x(), _input.getSize().y(), &gx[0], &gy[0]);
	edtaa3(&data[0], &gx[0], &gy[0], _input.getSize().x(), _input.getSize().y(), &xdist[0], &ydist[0], &outside[0]);
	for(size_t iii = 0; iii < outside.size(); ++iii) {
		if( outside[iii] < 0 ) {
			outside[iii] = 0.0;
		}
	}
	
	// Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
	for(size_t iii = 0; iii < gx.size(); ++iii) {
		gx[iii] = 0;
	}
	for(size_t iii = 0; iii < gy.size(); ++iii) {
		gy[iii] = 0;
	}
	for(size_t iii = 0; iii < data.size(); ++iii) {
		data[iii] = 1 - data[iii];
	}
	computegradient( &data[0], _input.getSize().x(), _input.getSize().y(), &gx[0], &gy[0]);
	edtaa3(&data[0], &gx[0], &gy[0], _input.getSize().x(), _input.getSize().y(), &xdist[0], &ydist[0], &inside[0]);
	for(size_t iii = 0; iii < inside.size(); ++iii) {
		if( inside[iii] < 0 ) {
			inside[iii] = 0.0;
		}
	}
	
	_output.resize(_input.getSize(), etk::Color<>(0));
	_output.clear(etk::Color<>(0));
	for (int32_t xxx = 0; xxx < _output.getSize().x(); ++xxx) {
		for (int32_t yyy = 0; yyy < _output.getSize().y(); ++yyy) {
			int32_t iii = yyy * _output.getSize().x() + xxx;
			outside[iii] -= inside[iii];
			outside[iii] = 128+outside[iii]*16;
			if( outside[iii] < 0 ) {
				outside[iii] = 0;
			}
			if( outside[iii] > 255 ) {
				outside[iii] = 255;
			}
			uint8_t val = 255 - (unsigned char) outside[iii];
			// TODO : Remove multiple size of the map ...
			_output.set(ivec2(xxx, yyy), etk::Color<>((int32_t)val,(int32_t)val,(int32_t)val,(int32_t)val));
		}
	}
	*/
}


bool egami::generateDistanceFieldFile(const etk::Uri& _input, const etk::Uri& _output) {
	egami::Image data;
	etk::String extention = etk::toLower(_input.getPath().getExtention());
	if (extention == "edf") {
		return false;
	}
	EGAMI_ERROR("Generate distance field : '" << _input << "' ==> '" << _output << "'");
	data = egami::load(_input, ivec2(64*5,64*5));
	if (data.exist() == false) {
		return false;
	}
	// Generate distance field:
	egami::ImageMono input;
	/*
	input.resize(data.getSize());
	for (int32_t yyy = 0; yyy < data.getSize().y(); ++yyy) {
		for (int32_t xxx = 0; xxx < data.getSize().x(); ++xxx) {
			input.set(ivec2(xxx, yyy), data.get(ivec2(xxx, yyy)).a() );
		}
	}
	*/
	generateDistanceField(input, data);
	// scale:
	data.scale(ivec2(64,64));
	// store:
	return egami::store(data, _output);
}

