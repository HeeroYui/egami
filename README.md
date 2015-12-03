egami
=====

`egami` is a simple wrapper to decode image file in etk image format.

Release (master)
----------------

[![Build Status](https://travis-ci.org/atria-soft/egami.svg?branch=master)](https://travis-ci.org/atria-soft/egami)
[![Coverage Status](http://atria-soft.com/ci/coverage/atria-soft/egami.svg?branch=master)](http://atria-soft.com/ci/atria-soft/egami)
[![Test Status](http://atria-soft.com/ci/test/atria-soft/egami.svg?branch=master)](http://atria-soft.com/ci/atria-soft/egami)
[![Warning Status](http://atria-soft.com/ci/warning/atria-soft/egami.svg?branch=master)](http://atria-soft.com/ci/atria-soft/egami)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=master&tag=Linux)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=master&tag=MacOs)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=master&tag=Mingw)](http://atria-soft.com/ci/atria-soft/egami)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=master&tag=Android)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=master&tag=IOs)](http://atria-soft.com/ci/atria-soft/egami)

Developement (dev)
------------------

[![Build Status](https://travis-ci.org/atria-soft/egami.svg?branch=dev)](https://travis-ci.org/atria-soft/egami)
[![Coverage Status](http://atria-soft.com/ci/coverage/atria-soft/egami.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/egami)
[![Test Status](http://atria-soft.com/ci/test/atria-soft/egami.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/egami)
[![Warning Status](http://atria-soft.com/ci/warning/atria-soft/egami.svg?branch=dev)](http://atria-soft.com/ci/atria-soft/egami)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=dev&tag=Linux)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=dev&tag=MacOs)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=dev&tag=Mingw)](http://atria-soft.com/ci/atria-soft/egami)

[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=dev&tag=Android)](http://atria-soft.com/ci/atria-soft/egami)
[![Build Status](http://atria-soft.com/ci/build/atria-soft/egami.svg?branch=dev&tag=IOs)](http://atria-soft.com/ci/atria-soft/egami)


Instructions
============

download Build system:
----------------------

	sudo pip install lutin
	sudo pip install pillow

download the software:
----------------------

	mkdir WORKING_DIRECTORY
	cd WORKING_DIRECTORY
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/exml.git
	git clone https://github.com/atria-soft/esvg.git
	git clone https://github.com/atria-soft/egami.git
	git clone https://github.com/generic-library/gtest-lutin.git --recursive
	git clone https://github.com/generic-library/z-lutin.git --recursive
	git clone https://github.com/generic-library/png-lutin.git --recursive
	git clone https://github.com/generic-library/edtaa3-lutin.git --recursive
	git clone https://github.com/generic-library/z-lutin.git --recursive

Compile software:
-----------------

	cd WORKING_DIRECTORY
	lutin -C -P egami-test


License (APACHE v2.0)
=====================
Copyright egami Edouard DUPIN

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

