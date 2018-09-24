/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etk/types.hpp>
#include <egami/debug.hpp>
#include <egami/Image.hpp>
#include <egami/wrapperEDF.hpp>
#include <etk/uri/uri.hpp>

//EDF format is a simple format for image in text for distance field image (special case)
// it is composed of the fist line : description of type (starting with #EDF and some other information, the data start just after the first \n

egami::Image egami::loadEDF(const etk::Uri& _uri) {
	egami::Image out;
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EGAMI_ERROR("Can not create the uri: " << _uri);
		return out;
	}
	if (fileIo->open(etk::io::OpenMode::Read) == false) {
		EGAMI_ERROR("Can not open (r) the file : " << _uri);
		return out;
	}
	etk::String line;
	fileIo->gets(line);
	if (etk::start_with(line, "#edf", false) == false) {
		EGAMI_ERROR("This file seams not to be a EDF file ...");
		fileIo->close();
		return out;
	}
	// count number of colomn max an number of line max:
	ivec2 size(0,0);
	while (fileIo->gets(line) == true) {
		if (line.size()/2 > (size_t)size.x()) {
			size.setValue(line.size()/2, size.y()+1);
		} else {
			size += ivec2(0,1);
		}
	}
	if (line.size()/2 > (size_t)size.x()) {
		size.setValue(line.size()/2, size.y()+1);
	} else {
		size += ivec2(0,1);
	}
	EGAMI_DEBUG("'" << _uri << "' ==> size=" << size);
	// jup to the start of the file
	fileIo->seek(0, etk::io::SeekMode::Start);
	// drop the first line
	fileIo->gets(line);
	// resize output:
	out.configure(size, egami::colorType::RGB8); // TODO : Do it better
	int32_t currentLineId = 0;
	char tmp[3];
	tmp[2] = '\0';
	while (fileIo->gets(line) == true) {
		if (line.size() <= 0) {
			continue;
		}
		for (size_t xxx = 0; xxx < line.size()-1; xxx+=2) {
			tmp[0] = line[xxx];
			tmp[1] = line[xxx+1];
			int32_t val = 0;
			sscanf(tmp, "%x", &val);
			out.set(ivec2(xxx/2, currentLineId), etk::Color<>((uint8_t)val, (uint8_t)val, (uint8_t)val, (uint8_t)val));
		}
		++currentLineId;
	}
	if (line.size() > 0) {
		for (size_t xxx = 0; xxx < line.size()-1; xxx+=2) {
			tmp[0] = line[xxx];
			tmp[1] = line[xxx+1];
			int32_t val = 0;
			sscanf(tmp, "%x", &val);
			out.set(ivec2(xxx/2, currentLineId), etk::Color<>((uint8_t)val, (uint8_t)val, (uint8_t)val, (uint8_t)val));
		}
	}
	fileIo->close();
	return out;
}

bool egami::storeEDF(const etk::Uri& _uri, const egami::Image& _inputImage) {
	bool anErrorEccured = false;
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EGAMI_ERROR("Can not create the uri: " << _uri);
		return false;
	}
	if (fileIo->open(etk::io::OpenMode::Write) == false) {
		EGAMI_ERROR("Can not open (w) the file : " << _uri);
		return false;
	}
	anErrorEccured = fileIo->puts(   etk::String("#EDF // Generate with EGAMI (")
	                               + etk::toString(_inputImage.getSize().x())
	                               + ","
	                               + etk::toString(_inputImage.getSize().y()) + ")\n");
	
	char tmp[256];
	for (int32_t yyy = 0; yyy < _inputImage.getSize().y(); ++yyy) {
		if (yyy != 0) {
			if (fileIo->put('\n') == false) {
				anErrorEccured = false;
			}
		}
		for (int32_t xxx = 0; xxx < _inputImage.getSize().x(); ++xxx) {
			sprintf(tmp, "%02X", _inputImage.get(ivec2(xxx, yyy)).a());
			/*
			if (yyy == 25) {
				EGAMI_DEBUG(" set : " << _inputImage.get(ivec2(xxx, yyy)) << " : '" << tmp << "'");
			}
			*/
			if (fileIo->puts(tmp) == false) {
				anErrorEccured = false;
			}
		}
	}
	fileIo->close();
	return anErrorEccured;
}
