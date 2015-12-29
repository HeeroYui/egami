#!/usr/bin/python
import lutin.module as module
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
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def get_version():
	return [0,2,0]

def create(target, module_name):
	my_module = module.Module(__file__, module_name, get_type())
	my_module.add_extra_compile_flags()
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
		'egami/Image.h',
		'egami/ImageMono.h',
		'egami/egami.h',
		])
	my_module.add_module_depend(['etk', 'png', 'esvg', 'edtaa3'])
	my_module.compile_flags('c++', [
		'-Wno-write-strings',
		'-Wall'])
	my_module.add_path(tools.get_current_path(__file__))
	return my_module


