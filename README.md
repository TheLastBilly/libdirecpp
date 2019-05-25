# libdirecpp

libdirecpp is a C/C++ library used to control Terminal Node Controllers (TNCs) for amateur radio. This is heavily based on the [Direwolf](https://github.com/wb2osz/direwolf) project by [wb2osz](https://github.com/wb2osz) and it's primarily meant to work with it.

## What can it do?

* Communicate with TNCs over tcp/serial using the KISS protocol
* Parse and create APRS packets

## How can I install it?

### Requirements

* g++
* make
* cmake

### Installation

At the moment, there's no a official installation method, so feel free to clone this library into your projects and use it as you so choose. The easiest method that works for me it's just to make a CMakeLists.txt file and add libdirecpp to project's sources.

For example:
```
CMakeLists.txt file:
--------------------

cmake_minimum_required(VERSION 3.0)
project ("myproject")

add_compile_options(-std=c++11)

file(GLOB SOURCES
    path/to/libdirecpp/src/include/*.hpp
    path/to/libdirecpp/src/*.cpp
    ...
    (My project's sources)
)

set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable( myproject ${SOURCES} )
```

And then just run cmake (I recommend you do it on a separate folder).

```
mkdir build
cd build
cmake ..
```

Lastly just type `make` to compile your code!

## And how do I use it?

I have prepared a few examples on the [examples](https://github.com/TheLastBilly/libdirecpp/tree/master/examples) folder, so you can take a look in there to see a basic use case of the library. For a more detail explanation, you can look at the documentation at the [doc](https://github.com/TheLastBilly/libdirecpp/tree/master/doc) folder.

### Compiling examples

Just go to the folder where the exmaple's `CMakeLists.txt` file is located, and type the following commands to compile it:

```
mkdir build
cd build
cmake ..
```

Then, while inside that same directory, type `bin/[name of the example]` to run it.

## Resources
* [AX.25 Link-Layer Protocol Specification](https://tapr.org/pub_ax25.html)
* [The KISS TNC: A simple Host-to-TNC communications protocol](http://www.ax25.net/kiss.aspx)
* [Direwolf - ax25_pad.c](https://github.com/wb2osz/direwolf/blob/master/ax25_pad.c)
* [Dire Wolf User Guide](https://github.com/wb2osz/direwolf/blob/master/doc/User-Guide.pdf)
* [Gtkmm Documentation](https://developer.gnome.org/gtkmm-tutorial/stable/index.html)
