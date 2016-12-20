#!/usr/bin/python
import lutin.debug as debug
import lutin.tools as tools
import os

def get_type():
	return "BINARY"

def get_sub_type():
	return "TOOL"

def get_desc():
	return "egami simple image viewer (visual)"

def get_licence():
	return "APACHE-2"

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
	    'appl/init.cpp',
	    'appl/MainWindows.cpp',
	    ])
	
	my_module.add_depend(['ewol'])
	
	my_module.copy_file('data/icon.png','icon.png')
	
	my_module.add_path(".")
	
	"""
	# set the package properties :
	my_module.pkg_set("VERSION", versionID)
	my_module.pkg_set("COMPAGNY_TYPE", "org")
	my_module.pkg_set("COMPAGNY_NAME", "Edouard DUPIN")
	my_module.pkg_set("MAINTAINER", ["Mr DUPIN Edouard <yui.heero@gmail.com>"])
	my_module.pkg_set("ICON", tools.get_current_path(__file__) + "/../data/icon.png")
	my_module.pkg_set("SECTION", ["Development"])
	my_module.pkg_set("PRIORITY", "optional")
	my_module.pkg_set("DESCRIPTION", "ewol test software")
	my_module.pkg_set("NAME", "test software")
	
	my_module.pkg_add("RIGHT", "SET_ORIENTATION")
	my_module.pkg_add("RIGHT", "VIBRATE")
	"""
	
	return True




