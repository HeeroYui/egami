Build lib & build sample                           {#exml_build}
========================

@tableofcontents

Download:                                          {#exml_build_download}
=========

exml use some tools to manage source and build it:

lutin (build-system):                              {#exml_build_download_lutin}
---------------------

```{.sh}
	pip install lutin --user
	# optionnal dependency of lutin (manage image changing size for application release)
	pip install pillow --user
```


dependency:                                        {#exml_build_download_dependency}
-----------

```{.sh}
	mkdir framework
	cd framework
	git clone https://github.com/atria-soft/elog.git
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/ememory.git
	cd ..
```

sources:                                           {#exml_build_download_sources}
--------

```{.sh}
	cd framework
	git clone https://github.com/atria-soft/exml.git
	cd ..
```

Build:                                             {#exml_build_build}
======


library:                                           {#exml_build_build_library}
--------

```{.sh}
	lutin -mdebug exml
```

Sample:                                            {#exml_build_build_sample}
-------

```{.sh}
	lutin -mdebug exml-sample
```


Run sample:                                        {#exml_build_run_sample}
===========

```{.sh}
	lutin -mdebug exml-sample?run
```
