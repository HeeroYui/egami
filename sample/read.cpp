/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

//! [egami_sample_read_all]
#include <test-debug/debug.hpp>
#include <etk/math/Vector2D.hpp>
//! [egami_sample_include]
#include <egami/egami.hpp>
//! [egami_sample_include]
#include "read.hpp"


static void readBMP() {
	//! [egami_sample_declare_image]
	// create an empty Image (no type and no inside data)
	egami::Image image;
	//! [egami_sample_declare_image]
	//! [egami_sample_read_file_bmp]
	image = egami::load("DATA:read.bmp");
	//! [egami_sample_read_file_bmp]
	TEST_INFO("image exist (BMP): " << image.exist());
}

static void readSVG() {
	//! [egami_sample_read_file_svg]
	egami::Image image = egami::load("DATA:read.svg");
	//! [egami_sample_read_file_svg]
	TEST_INFO("image exist (SVG): " << image.exist());
	//! [egami_sample_read_file_svg_rescale]
	image = egami::load("DATA:read.svg", ivec2(800,600));
	//! [egami_sample_read_file_svg_rescale]
	TEST_INFO("image exist (SVG-rescale): " << image.exist());
	//! [egami_sample_read_file_svg_scale_factor]
	// TODO : image = egami::load("DATA:read.svg", 0.5);
	//! [egami_sample_read_file_svg_scale_factor]
	TEST_INFO("image exist (SVG-scale): " << image.exist());
}

static void readPNG() {
	//! [egami_sample_read_file_png]
	egami::Image image = egami::load("DATA:read.png");
	//! [egami_sample_read_file_png]
	TEST_INFO("image exist (PNG): " << image.exist());
}


void appl::read() {
	readBMP();
	readSVG();
	readPNG();
}
//! [egami_sample_read_all]