EXML library                                {#mainpage}
============

@tableofcontents

What is EXML:                               {#exml_mainpage_what}
==================

EXML, or Ewol XML interface is a simple, small, efficient, C++ XML parser/generator that can be easily integrating into other programs.

What it does:                               {#exml_mainpage_what_it_does}
-------------

EXML parses an XML document, and builds from that a Document Object Model (DOM) that can be read, modified, and saved.

XML stands for "eXtensible Markup Language." It is a general purpose human and machine readable markup language to describe arbitrary data.
All those random file formats created to store application data can all be replaced with XML. One parser for everything.

http://wikipedia.org/wiki/XML

There are different ways to access and interact with XML data.
EXML uses a Document Object Model (DOM), meaning the XML data is parsed into a C++ objects that can be browsed and manipulated, and then written to disk.
You can also construct an XML document from scratch with C++ objects and write this to disk.

EXML is designed to be easy and fast to learn.

EXML is dependent of the STL (compatible with MacOs stl (CXX))

What it doesn't do:                          {#exml_mainpage_what_it_not_does}
-------------------

EXML doesn't parse or use DTDs (Document Type Definitions) or XSLs (eXtensible Stylesheet Language).

What languages are supported?                    {#exml_mainpage_language}
=============================

EXML is written in C++.


Are there any licensing restrictions?            {#exml_mainpage_license_restriction}
=====================================

EXML is **FREE software** and _all sub-library are FREE and staticly linkable !!!_


License (APACHE-2.0)                             {#exml_mainpage_license}
====================

Copyright EXML Edouard DUPIN

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

<http://www.apache.org/licenses/LICENSE-2.0>

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Other pages                              {#exml_mainpage_sub_page}
===========

  - @ref exml_build
  - @ref exml_tutorial_read
  - @ref exml_tutorial_write
  - [**ewol coding style**](http://atria-soft.github.io/ewol/ewol_coding_style.html)

