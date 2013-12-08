#!/usr/bin/python
import lutinModule
import lutinTools

def Create(target):
	# module name is 'edn' and type binary.
	myModule = lutinModule.module(__file__, 'egami', 'LIBRARY')
	# enable doculentation :
	myModule.doc_enable()
	myModule.documentation.set_website("http://HeeroYui.github.io/egami/")
	myModule.documentation.set_path(lutinTools.GetCurrentPath(__file__) + "/egami/")
	myModule.documentation.set_external_link(['etk', 'png', 'esvg'])
	
	# add extra compilation flags :
	myModule.add_extra_compile_flags()
	# add the file to compile:
	myModule.AddSrcFile([
		'egami/Image.cpp',
		'egami/egami.cpp',
		'egami/debug.cpp',
		'egami/wrapperPNG.cpp',
		'egami/wrapperSVG.cpp',
		'egami/wrapperBMP.cpp'])
	
	# name of the dependency
	myModule.AddModuleDepend(['etk', 'png', 'esvg'])
	
	myModule.CompileFlags_CC([
		'-Wno-write-strings',
		'-Wall'])
	
	myModule.AddExportPath(lutinTools.GetCurrentPath(__file__))
	
	
	# add the currrent module at the 
	return myModule


