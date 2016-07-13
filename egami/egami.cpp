/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <egami/egami.h>
#include <egami/debug.h>

#include <egami/wrapperSVG.h>
#include <egami/wrapperPNG.h>
#include <egami/wrapperBMP.h>
#include <egami/wrapperEDF.h>
#include <edtaa3/edtaa3func.h>

bool egami::scalable(const std::string& _fileName) {
	if (true == etk::end_with(_fileName, ".svg") ) {
		return true;
	}
	return false;
}

egami::Image egami::load(const std::string& _fileName, const ivec2& _size) {
	std::string tmpName = etk::tolower(_fileName);
	egami::Image out;
	// select the corect Loader :
	if (etk::end_with(tmpName, ".edf") == true) {
		// internal format for ewol distance field ==> simple sistance field image
		out = egami::loadEDF(_fileName);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load EDF file '" << _fileName << "'");
		}
	} else if (etk::end_with(tmpName, ".bmp") == true) {
		out = egami::loadBMP(_fileName);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load BMP file '" << _fileName << "'");
		}
	} else if (etk::end_with(tmpName, ".svg") == true) {
		out = egami::loadSVG(_fileName, _size);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load SVG file '" << _fileName << "'");
		}
		//egami::storeEDF(_fileName + ".edf", _output);
	} else if (etk::end_with(tmpName, ".png") == true) {
		out = egami::loadPNG(_fileName);
		if (out.exist() == false) {
			EGAMI_ERROR("Error to load PNG file '" << _fileName << "'");
		}
	} else {
		EGAMI_ERROR("Extention not managed '" << _fileName << "' Sopported extention : .edf / .bmp / .svg / .png");
	}
	return out;
}

bool egami::store(const egami::Image& _input, const std::string& _fileName) {
	std::string tmpName = etk::tolower(_fileName);
	EGAMI_DEBUG("Store file : " << _fileName);
	// select the corect Loader :
	if (etk::end_with(tmpName, ".edf") == true) {
		if (egami::storeEDF(_fileName, _input) == false) {
			EGAMI_ERROR("Error to load EDF file '" << _fileName << "'");
			return false;
		}
	} else if (etk::end_with(tmpName, ".bmp") == true) {
		if (egami::storeBMP(_fileName, _input) == false) {
			EGAMI_ERROR("Error to load BMP file '" << _fileName << "'");
			return false;
		}
	} else if (etk::end_with(tmpName, ".svg") == true) {
		EGAMI_ERROR("Can not store in SVG file '" << _fileName << "'");
		return false;
	} else if (etk::end_with(tmpName, ".png") == true) {
		EGAMI_ERROR("Can not store in PNG file '" << _fileName << "'");
		return false;
	} else {
		EGAMI_ERROR("Extention not managed '" << _fileName << "' Sopported extention : .bmp / .svg / .png");
		return false;
	}
	return true;
}



static void generateDistanceField(const egami::ImageMono& _input, egami::Image& _output) {
	int32_t size = _input.getSize().x() * _input.getSize().y();
	std::vector<short> xdist(size);
	std::vector<short> ydist(size);
	std::vector<double> gx(size);
	std::vector<double> gy(size);
	std::vector<double> data(size);
	std::vector<double> outside(size);
	std::vector<double> inside(size);
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


bool egami::generateDistanceFieldFile(const std::string& _input, const std::string& _output) {
	egami::Image data;
	if (etk::end_with(_input, ".edf") == true) {
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

