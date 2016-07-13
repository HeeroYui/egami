Write an XML content                                {#exml_tutorial_write}
====================

@tableofcontents

The first thing to do when reading or writing a XML file/stream, is to declare the Document interface

Include exml
@snippet read.cpp exml_sample_include

Declare document interface
@snippet read.cpp exml_sample_declare_doc


Write an XML file                                  {#exml_tutorial_write_file}
=================

Write an xml tree is done like:
@snippet write.cpp exml_sample_write_file


Write an XML Stream                                {#exml_tutorial_write_stream}
===================

Writing a stream is done like this:
@snippet write.cpp exml_sample_write_stream

Operation on Tree                                  {#exml_tutorial_write_operation}
=================

Add Node/Declaration:
@snippet write.cpp exml_sample_write_add_declaration

Add an Node/Element:
@snippet write.cpp exml_sample_write_add_element

Remove a Node/Element:
@snippet write.cpp exml_sample_write_rm_node


Add an attribute (simple version):
@snippet write.cpp exml_sample_write_add_attribute_simple

Add an attribute (complex version):
@snippet write.cpp exml_sample_write_add_attribute_complex

Remove an attribute:
@snippet write.cpp exml_sample_write_rm_attribute

Object concept                                    {#exml_tutorial_concept}
==============

the exml concept is to abstract the implementation of the internal system. All the element are maped on shared memory.
Then if you asign an element to an other, it is the same. You need to clone it if you want to have new standalone element.


All example file                                  {#exml_tutorial_write_all}
================

@snippet write.cpp exml_sample_write_all

