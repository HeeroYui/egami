#!/usr/bin/python
import lutin.module as module
import lutin.tools as tools

def get_desc():
	return "Test software for egami"

def get_licence():
	return {
		"assimilate":"APACHE2",
		"type":"APACHE-2.0"
		}

def create(target):
	myModule = module.Module(__file__, 'egami-test', 'BINARY')
	
	myModule.add_module_depend(['egami', 'gtest', 'test-debug'])
	
	myModule.add_src_file([
		'test/main.cpp'
		])
	
	myModule.add_export_path(tools.get_current_path(__file__))
	
	# add the currrent module at the 
	return myModule







