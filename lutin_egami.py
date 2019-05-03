#!/usr/bin/python
import realog.debug as debug
import lutin.tools as tools


def get_type():
	return "LIBRARY"

def get_desc():
	return "image generator from multiple image type"

def get_licence():
	return "MPL-2"

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
	    'edtaa3'
	    ])
	my_module.add_flag('c++', [
	    '-Wno-write-strings',
	    '-Wall'
	    ])
	my_module.add_optionnal_depend(
	    'png',
	    ["c++", "-DEGAMI_BUILD_PNG"],
	    src_file=[
	        'egami/wrapperPNG.cpp',
	        ]
	    )
	my_module.add_optionnal_depend(
	    'esvg',
	    ["c++", "-DEGAMI_BUILD_ESVG"],
	    src_file=[
	        'egami/wrapperSVG.cpp',
	        ]
	    )
	my_module.add_optionnal_depend(
	    'jpeg',
	    ["c++", "-DEGAMI_BUILD_JPEG"],
	    src_file=[
	        'egami/wrapperJPG.cpp',
	        ]
	    )
	my_module.add_optionnal_depend(
	    'openjpeg',
	    ["c++", "-DEGAMI_BUILD_JPEG2000"],
	    src_file=[
	        'egami/wrapperJPG2000.cpp',
	        ]
	    )
	my_module.add_optionnal_depend(
	    'tiff',
	    ["c++", "-DEGAMI_BUILD_TIFF"],
	    src_file=[
	        'egami/wrapperTIFF.cpp',
	        ]
	    )
	my_module.add_path(".")
	return True


