/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
#include <etk/etk.hpp>
#include <gtest/gtest.h>
#include <egami/egami.hpp>
#include <algue/sha512.hpp>


int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// init etk log system and file interface:
	etk::init(argc, argv);
	// Run all test with gtest
	return RUN_ALL_TESTS();
}

TEST(TestBMP, read_227x149) {
	egami::Image image = egami::load("DATA:read_227x149.bmp");
	egami::store(image, "out/read_227x149.bmp.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(227,149), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("3518a9693a349044d23c3a95262831144011086fdb339ef8532f9c6cebffe76b2c994b0a3e6d69addca15538a1cb559af3be445c5b622b5cf80c9291e7b8ca5b", sha512);
}

TEST(TestBMP, read_128x128) {
	egami::Image image = egami::load("DATA:read_128x128.bmp");
	egami::store(image, "out/read_128x128.bmp.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(128,128), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("3518a9693a349044d23c3a95262831144011086fdb339ef8532f9c6cebffe76b2c994b0a3e6d69addca15538a1cb559af3be445c5b622b5cf80c9291e7b8ca5b", sha512);
}


TEST(TestPNG, read_227x149) {
	egami::Image image = egami::load("DATA:read_227x149.png");
	egami::store(image, "out/read.png_227x149.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(227,149), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("42dbad7abf1e651da58c9df06521d63a878b5bd0db6e1cbe129db3c9782ce640a6709583ba9e6571d314f39b259321dcc392f98bf4412deb5ce8392566d2bc0f", sha512);
}

TEST(TestPNG, read_128x128) {
	egami::Image image = egami::load("DATA:read_128x128.png");
	egami::store(image, "out/read_128x128.png.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(227,149), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("42dbad7abf1e651da58c9df06521d63a878b5bd0db6e1cbe129db3c9782ce640a6709583ba9e6571d314f39b259321dcc392f98bf4412deb5ce8392566d2bc0f", sha512);
}

TEST(TestSVG, read) {
	egami::Image image = egami::load("DATA:read.svg");
	egami::store(image, "out/read.svg.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(64,64), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGBA8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("7975d12caae94e67e85909f26b6dc0672d7e4686808d851b3207be6272b6d0153572cd643eea819c2f4dae9f7837165b4d5b34353da9f847d77afc2701945284", sha512);
}


TEST(TestJPG, read_227x149) {
	egami::Image image = egami::load("DATA:read_227x149.jpg");
	egami::store(image, "out/read_227x149.jpg.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(227,149), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("42dbad7abf1e651da58c9df06521d63a878b5bd0db6e1cbe129db3c9782ce640a6709583ba9e6571d314f39b259321dcc392f98bf4412deb5ce8392566d2bc0f", sha512);
}


TEST(TestJPG, read_128x128) {
	egami::Image image = egami::load("DATA:read_128x128.jpg");
	egami::store(image, "out/read_128x128.jpg.bmp");
	// Check if image is loaded
	EXPECT_EQ(true, image.exist());
	// check image correct size
	EXPECT_EQ(ivec2(227,149), image.getSize());
	// check image correct type
	EXPECT_EQ(egami::colorType::RGB8, image.getType());
	// check integrity
	std::string sha512 = algue::stringConvert(algue::sha512::encode((const uint8_t *)image.getTextureDataPointer(), egami::getFormatColorSize(image.getType()) * image.getSize().x() * image.getSize().y()));
	EXPECT_EQ("42dbad7abf1e651da58c9df06521d63a878b5bd0db6e1cbe129db3c9782ce640a6709583ba9e6571d314f39b259321dcc392f98bf4412deb5ce8392566d2bc0f", sha512);
}
