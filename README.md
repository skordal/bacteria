Bacteria Read-me-not
====================

Bacteria is a simple bacteria simulator, where you can watch your little bacteria friends eat, multiply and die. The simulation ends when all your bacteria has died.

There are a few commands you can give the simulator when it's running, see the file docs/controls.txt.

To build the simulator, you need to have the following prerequisites installed:

* CMake   - the build system utilized.
* SDL     - for graphics.
* SDL\_ttf - for text.

To build on a Unixy system, use the following commands:

	cmake .
	make

To build on other platforms, you will have to find your own way. CMake is multi-platform, as is SDL, so it is possible, but Bacteria has not been tested on anything other than Linux.

The code is MIT licensed, see the COPYING.md file for details.

Please report any issues on <http://github.com/skordal/bacteria/issues>.

