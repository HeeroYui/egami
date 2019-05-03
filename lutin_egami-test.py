#!/usr/bin/python
import realog.debug as debug
import lutin.tools as tools


def get_type():
	return "BINARY"

def get_sub_type():
	return "TEST"

def get_desc():
	return "Test software for egami"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def configure(target, my_module):
	my_module.add_depend([
	    'egami',
	    'etest',
	    'test-debug',
	    'algue',
	    ])
	my_module.add_src_file([
	    'test/main.cpp'
	    ])
	my_module.copy_path('data/*')
	return True







