cmake_minimum_required(VERSION 2.8)

# Declare the project
project(egami)

##
## Include C++ X11 dependency ... (check correct flags)
##
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()


# set output path:
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(.)

#Create src file list
set(src_files
	egami/Image.cpp
	egami/Image.h
	egami/ImageMono.cpp
	egami/ImageMono.h
	egami/egami.cpp
	egami/egami.h
	egami/debug.cpp
	egami/debug.h
	egami/wrapperPNG.cpp
	egami/wrapperPNG.h
	egami/wrapperSVG.cpp
	egami/wrapperSVG.h
	egami/wrapperBMP.cpp
	egami/wrapperBMP.h
	egami/wrapperEDF.cpp
	egami/wrapperEDF.h
)

add_definitions( -DDEBUG_LEVEL=3 )
add_definitions( -DDEBUG=1 )
if (APPLE)
	add_definitions( -D__TARGET_OS__MacOs )
elseif (UNIX)
	add_definitions( -D__TARGET_OS__Linux )
elseif (WIN32)
	add_definitions( -D__TARGET_OS__Windows )
endif ()


include_directories(${etk_SOURCE_DIR})
include_directories(${linearmath_SOURCE_DIR}/bullet/src/)
include_directories(${agg_SOURCE_DIR})
include_directories(${esvg_SOURCE_DIR})
include_directories(${edtaa3_SOURCE_DIR})
include_directories(${png_SOURCE_DIR})
include_directories(${exml_SOURCE_DIR})

#Create a static Lib:
add_library(egami STATIC ${src_files} )
target_link_libraries(egami etk agg)
