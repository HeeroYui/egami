#!/usr/bin/python
import lutinModule as module
import lutinTools as tools
import lutinTools

def get_desc():
	return "e-gami library (image generator from multiple image type)"

def create(target):
	# module name is 'edn' and type binary.
	myModule = module.Module(__file__, 'egami', 'LIBRARY')
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.add_src_file([
		'egami/Image.cpp',
		'egami/egami.cpp',
		'egami/debug.cpp',
		'egami/wrapperPNG.cpp',
		'egami/wrapperSVG.cpp',
		'egami/wrapperBMP.cpp'])
	
	# name of the dependency
	myModule.add_module_depend(['etk', 'png', 'esvg'])
	
	myModule.compile_flags_CC([
		'-Wno-write-strings',
		'-Wall'])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	
	# add the currrent module at the 
	return myModule


