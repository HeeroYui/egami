/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

//! [egami_sample_write_all]
#include <test-debug/debug.hpp>
#include <egami/egami.hpp>
#include "write.hpp"


static void writeBMP() {
	//! [egami_sample_create_image]
	// create an empty Image (no type and no inside data)
	egami::Image image(ivec2(25,25), egami::colorType::RGBA8);
	image.set(ivec2(5,5), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(12,15), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(4,9), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	// ...
	//! [egami_sample_create_image]
	//! [egami_sample_write_file_bmp]
	bool ret = egami::store(image, "out/egami_test_write.bmp");
	//! [egami_sample_write_file_bmp]
	TEST_INFO("image write (BMP): " << ret);
}

static void writeSVG() {
	TEST_INFO("image write (SVG): Not Avaliiable");
}

static void writePNG() {
	// create an empty Image (no type and no inside data)
	egami::Image image(ivec2(25,25), egami::colorType::RGBA8);
	image.set(ivec2(5,5), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(12,15), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(4,9), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	// ...
	//! [egami_sample_write_file_png]
	bool ret = egami::store(image, "out/egami_test_write.png");
	//! [egami_sample_write_file_png]
	TEST_INFO("image write (PNG): " << ret);
}
static void writeJPG() {
	// create an empty Image (no type and no inside data)
	egami::Image image(ivec2(25,25), egami::colorType::RGBA8);
	image.set(ivec2(5,5), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(12,15), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	image.set(ivec2(4,9), etk::Color<>(0x88, 0xFF, 0x00, 0xFF));
	// ...
	//! [egami_sample_write_file_jpg]
	bool ret = egami::store(image, "out/egami_test_write.jpg");
	//! [egami_sample_write_file_jpg]
	TEST_INFO("image write (JPG): " << ret);
}


void appl::write() {
	writeBMP();
	writeSVG();
	writePNG();
	writeJPG();
}
//! [egami_sample_write_all]


