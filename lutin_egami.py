#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "image generator from multiple image type"

def get_licence():
	return "APACHE-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return "authors.txt"

def get_version():
	return "version.txt"

def configure(target, my_module):
	my_module.add_extra_flags()
	my_module.add_src_file([
	    'egami/Image.cpp',
	    'egami/ImageMono.cpp',
	    'egami/egami.cpp',
	    'egami/debug.cpp',
	    'egami/wrapperPNG.cpp',
	    'egami/wrapperSVG.cpp',
	    'egami/wrapperBMP.cpp',
	    'egami/wrapperEDF.cpp'
	    ])
	my_module.add_header_file([
	    'egami/Image.hpp',
	    'egami/ImageMono.hpp',
	    'egami/egami.hpp',
	    ])
	my_module.add_depend([
	    'etk',
	    'png',
	    'esvg',
	    'edtaa3'
	    ])
	my_module.add_flag('c++', [
	    '-Wno-write-strings',
	    '-Wall'
	    ])
	my_module.add_path(".")
	return True


