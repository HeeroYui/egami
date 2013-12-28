#!/usr/bin/python
import monkModule as module
import monkTools as tools
import monkDebug as debug
import datetime

def get_desc():
	return "e-gami library (image generator from multiple image type)"

def create():
	# module name is 'egami' and type binary.
	myModule = module.Module(__file__, 'egami', 'LIBRARY')
	# enable doculentation :
	myModule.set_website("http://heeroyui.github.io/egami/")
	myModule.set_website_sources("http://github.com/heeroyui/egami/")
	myModule.set_path(tools.get_current_path(__file__) + "/egami/")
	
	# add the currrent module at the 
	return myModule


