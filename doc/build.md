Build lib & build sample                           {#egami_build}
========================

@tableofcontents

Download:                                          {#egami_build_download}
=========

egami use some tools to manage source and build it:

lutin (build-system):                              {#egami_build_download_lutin}
---------------------

```{.sh}
	pip install lutin --user
	# optionnal dependency of lutin (manage image changing size for application release)
	pip install pillow --user
```


dependency:                                        {#egami_build_download_dependency}
-----------

```{.sh}
	mkdir framework
	cd framework
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/exml.git
	git clone https://github.com/atria-soft/esvg.git
	git clone https://github.com/atria-soft/egami.git
	git clone https://github.com/generic-library/gtest-lutin.git --recursive
	git clone https://github.com/generic-library/z-lutin.git --recursive
	git clone https://github.com/generic-library/png-lutin.git --recursive
	git clone https://github.com/generic-library/edtaa3-lutin.git --recursive
	git clone https://github.com/generic-library/z-lutin.git --recursive
	cd ..
```

sources:                                           {#egami_build_download_sources}
--------

```{.sh}
	cd framework
	git clone https://github.com/atria-soft/egami.git
	cd ..
```

Build:                                             {#egami_build_build}
======


library:                                           {#egami_build_build_library}
--------

```{.sh}
	lutin -mdebug egami
```

Sample:                                            {#egami_build_build_sample}
-------

```{.sh}
	lutin -mdebug egami-sample
```


Run sample:                                        {#egami_build_run_sample}
===========

```{.sh}
	lutin -mdebug egami-sample?run
```
