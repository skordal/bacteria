# CMakeLists.txt file for Bakteria - the interesting game of bacteria
# (c) Kristian K. Skordal 2009 - 2012
cmake_minimum_required(VERSION 2.6)

project(bacteria)

set(SOURCE_FILES
	application.cpp
	bacteria.cpp
	config_db.cpp
	config_parser.cpp
	energy_bar.cpp
	food.cpp
	image.cpp
	logger.cpp
	main.cpp
	statistics.cpp
	vector.cpp
)

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
	message(FATAL_ERROR "Could not find SDL!")
endif(NOT SDL_FOUND)

if(NOT DISABLE_SDLTTF)
	find_package(SDL_ttf)
	if(NOT SDLTTF_FOUND)
		message("Could not find SDL_ttf!")
		message("Disabling SDL_ttf")
		set(CMAKE_CXX_FLAGS "-DDISABLE_SDLTTF")
		set(DISABLE_SDLTTF TRUE)
	endif(NOT SDLTTF_FOUND)
endif(NOT DISABLE_SDLTTF)

if(NOT DISABLE_SDLTTF)
	include_directories(${SDL_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR})
else(NOT DISABLE_SDLTTF)
	include_directories(${SDL_INCLUDE_DIR})
endif(NOT DISABLE_SDLTTF)

add_executable(bacteria ${SOURCE_FILES})
if(NOT DISABLE_SDLTTF)
	target_link_libraries(bacteria ${SDL_LIBRARY} ${SDLTTF_LIBRARY} rt)
else(NOT DISABLE_SDLTTF)
	target_link_libraries(bacteria ${SDL_LIBRARY} rt)
endif(NOT DISABLE_SDLTTF)

# Install image files:
install(FILES
		graphics/bacteria.bmp
		graphics/food.bmp
		graphics/red.bmp
		graphics/yellow.bmp
		graphics/green.bmp
		icon.png
	DESTINATION
		share/bacteria/graphics
)

# Install the font file:
install(FILES
		DejaVuSans.ttf
	DESTINATION
		share/bacteria
)

# Install the desktop file:
install(FILES
		bacteria.desktop
	DESTINATION
		share/applications
)

# Install the binary file:
install(PROGRAMS
		bacteria
	DESTINATION
		bin
)

# Install the documentation:
install(FILES
		docs/config.txt
		docs/controls.txt
		docs/quickstart.txt
	DESTINATION
		share/doc/bacteria
)

