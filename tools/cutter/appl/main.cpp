/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <appl/debug.hpp>
#include <etk/etk.hpp>
#include <egami/egami.hpp>

static void usage(int _retValue = 0) {
	APPL_PRINT("Help : ");
	APPL_PRINT("    ./xxx [options]");
	APPL_PRINT("        -h/--help:     Display this help");
	APPL_PRINT("        -i/--input:    Input of the calculator");
	APPL_PRINT("        -o/--output:   Output of the calculator");

	exit(_retValue);
}


int main(int argc, const char *argv[]) {
	// the only one init for etk:
	etk::init(argc, argv);
	etk::String input;
	etk::String output;
	for (int32_t iii=0; iii<argc ; ++iii) {
		etk::String data = argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			usage();
		} else if (data.startWith("-i=") == true) {
			input = etk::String(data.begin() + 3, data.end());
		} else if (data.startWith("--input=") == true) {
			input = etk::String(data.begin() + 8, data.end());
		} else if (data.startWith("-o=") == true) {
			output = etk::String(data.begin() + 3, data.end());
		} else if (data.startWith("--output=") == true) {
			output = etk::String(data.begin() + 9, data.end());
		}
	}
	if (input == "") {
		APPL_ERROR("Missing Input ...");
		usage(-1);
	}
	if (output == "") {
		APPL_ERROR("Missing output ...");
		usage(-1);
	}
	APPL_INFO("read [START] " << input);
	egami::Image image;
	image = egami::load(input);
	if (image.exist() == false) {
		APPL_ERROR("read [STOP ] ==> an error occured...");
		return -2;
	}
	APPL_INFO("read [STOP ]");
	
	ivec2 middle = image.getSize() / 2;
	
	APPL_INFO("Source Image Size:" << image.getSize());
	
	uint8_t baseValue = 0x40;
	
	// top:
	uint_t posTop = 0;
	uint_t posBottom = image.getSize().y();
	uint_t posLeft = 0;
	uint_t posRight = image.getSize().x();
	uint_t maxOutOfRange = 3;
	for (uint_t yyy=0; yyy<middle.y()-maxOutOfRange; ++yyy) {
		bool found = false;
		//APPL_DEBUG("Check position:" << yyy);
		for (uint_t iii=0; iii<maxOutOfRange; ++iii) {
			auto val1 = image.get(ivec2(middle.x(), yyy+iii));
				//APPL_VERBOSE("Check value:" << iii << "    " << val1);
			if (    val1.r() < baseValue
			     && val1.g() < baseValue
			     && val1.b() < baseValue) {
				found = true;
				break;
			}
		}
		if (found == true) {
			continue;
		}
		posTop = yyy;
		break;
	}
	APPL_INFO("Clip on TOP:" << posTop);
	for (uint_t yyy=image.getSize().y()-1; yyy>=middle.y()+maxOutOfRange; --yyy) {
		bool found = false;
		//APPL_DEBUG("Check position:" << yyy);
		for (uint_t iii=0; iii<maxOutOfRange; ++iii) {
			auto val1 = image.get(ivec2(middle.x(), yyy-iii));
				//APPL_VERBOSE("Check value:" << iii << "    " << val1);
			if (    val1.r() < baseValue
			     && val1.g() < baseValue
			     && val1.b() < baseValue) {
				found = true;
				break;
			}
		}
		if (found == true) {
			continue;
		}
		posBottom = yyy;
		break;
	}
	APPL_INFO("Clip on BOTTOM:" << posBottom);
	
	for (uint_t xxx=0; xxx<middle.x()-maxOutOfRange; ++xxx) {
		bool found = false;
		//APPL_DEBUG("Check position:" << yyy);
		for (uint_t iii=0; iii<maxOutOfRange; ++iii) {
			auto val1 = image.get(ivec2(xxx+iii, middle.y()));
				//APPL_VERBOSE("Check value:" << iii << "    " << val1);
			if (    val1.r() < baseValue
			     && val1.g() < baseValue
			     && val1.b() < baseValue) {
				found = true;
				break;
			}
		}
		if (found == true) {
			continue;
		}
		posLeft = xxx;
		break;
	}
	APPL_INFO("Clip on LEFT:" << posLeft);
	for (uint_t xxx=image.getSize().x()-1; xxx>=middle.x()+maxOutOfRange; --xxx) {
		bool found = false;
		//APPL_DEBUG("Check position:" << yyy);
		for (uint_t iii=0; iii<maxOutOfRange; ++iii) {
			auto val1 = image.get(ivec2(xxx-iii, middle.y()));
				//APPL_VERBOSE("Check value:" << iii << "    " << val1);
			if (    val1.r() < baseValue
			     && val1.g() < baseValue
			     && val1.b() < baseValue) {
				found = true;
				break;
			}
		}
		if (found == true) {
			continue;
		}
		posRight = xxx;
		break;
	}
	APPL_INFO("Clip on Right:" << posRight);
	
	image.resize(ivec2(image.getSize().x() - posLeft - (image.getSize().x() - posRight),
	                   image.getSize().y() - posTop - (image.getSize().y() - posBottom)),
	             ivec2(posLeft, posTop));
	
	APPL_INFO("output Image Size:" << image.getSize());
	APPL_INFO("write [START] " << output);
	bool ret = egami::store(image, output);
	if (ret == false) {
		APPL_ERROR("write [STOP ] ==> an error occured...");
		return -3;
	}
	APPL_INFO("write [STOP ]");
	return 0;
}
