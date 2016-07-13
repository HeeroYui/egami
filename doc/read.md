Read an XML content                                {#exml_tutorial_read}
===================

@tableofcontents

The first thing to do when reading or writing a XML file/stream, is to declare the Document interface

Include exml
@snippet read.cpp exml_sample_include

Declare document interface
@snippet read.cpp exml_sample_declare_doc


Read an XML file                                 {#exml_tutorial_read_file}
================

File to read: "read.xml"
@include read.xml

Reading a file is done like this:
@snippet read.cpp exml_sample_read_file

The file naming is manage by @ref etk::FSNode that provide "DATA:" start string for internal application asset. You can use external path like "./plop/file.xml" too.


Read an XML Stream                              {#exml_tutorial_read_stream}
==================

Reading a stream is done like this:
@snippet read.cpp exml_sample_read_stream1

In C and C++ it is very hard to read string with the \\" then to simplify parsing of xml the parser engine support the use of simple ' interface:
@snippet read.cpp exml_sample_read_stream2


Access at all Element datas                     {#exml_tutorial_read_folow}
===========================

In an exml::Element (or exml::Document) the sub-nodes are accessible threw an abstraction class stores in an element name **nodes**

Get a node with its name:
@snippet read.cpp exml_sample_read_get_node

Reading all file nodes:
@snippet read.cpp exml_sample_read_folow_nodes

**note:** the itElem is a simple exml::Node that can be all the xml type. you can change the type by calling: toDocument(), toElement(), toString() ...

In a C style mode:
@snippet read.cpp exml_sample_read_folow_nodes_c



In an exml::Element (or exml::Document or exml::Declaration) the sub-nodes are accessible threw an abstraction class stores in an element name **attributes**

Reading all Attributes of one node:
@snippet read.cpp exml_sample_read_folow_attributes

In a C style mode:
@snippet read.cpp exml_sample_read_folow_attributes_c

Get an attribute data:
@snippet read.cpp exml_sample_read_get_direct_attribute




In an exml::Element (or exml::Document) the internal data text can be accessible threw the interface:

Get all the data in an element in text mode:
@snippet read.cpp exml_sample_read_get_all_under_string



All example file                                  {#exml_tutorial_read_all}
================

@snippet read.cpp exml_sample_read_all

