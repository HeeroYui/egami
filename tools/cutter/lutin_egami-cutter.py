#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools
import os

def get_type():
	return "BINARY"

def get_sub_type():
	return "TOOL"

def get_desc():
	return "egami simple image cutter (bash tools)"

def get_licence():
	return "MPL-2"

def get_compagny_type():
	return "com"

def get_compagny_name():
	return "atria-soft"

def get_maintainer():
	return ["Mr DUPIN Edouard <yui.heero@gmail.com>"]

def configure(target, my_module):
	# add the file to compile:
	my_module.add_src_file([
	    'appl/debug.cpp',
	    'appl/main.cpp',
	    ])
	
	my_module.add_depend([
	    'egami',
	    ])
	
	#my_module.copy_file('data/icon.png','icon.png')
	
	my_module.add_path(".")
	
	return True




