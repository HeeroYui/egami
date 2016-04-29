/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <etk/etk.h>
#include <gtest/gtest.h>


int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// init etk log system and file interface:
	etk::init(argc, argv);
	// Run all test with gtest
	return RUN_ALL_TESTS();
}


TEST(TestPng, read) {
	// TODO : Do real test ...
	EXPECT_EQ(5, 6);
}

