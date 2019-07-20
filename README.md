# libdirecpp

libdirecpp is a C/C++ library used to control Terminal Node Controllers (TNCs) for amateur radio. This is heavily based on the [Direwolf](https://github.com/wb2osz/direwolf) project by [wb2osz](https://github.com/wb2osz) and it's primarily meant to work with it.

## What can it do?

* Communicate with TNCs over tcp/serial using the KISS protocol
* Parse and create APRS packets

## How can I install it?

### Requirements

* g++
* make
* autotools

### Installation
#### Requires sudo
Download a release version from this github repository and do de following commands on the directory it is located.

```
tar -xvf libdirecpp-x.x.x.tar.gz
cd libdirecpp-x.x.x.tar.gz
./configure
make
sudo make install
```
Note 1: x.x.x represents the release version you downloaded.

Note 2: You might have to create a symlink from `libdirecpp` to /usr/lib. You can do so by typing the following command:
```
sudo ln -s /usr/local/lib/libdirecpp.* /usr/lib/
```

## And how do I use it?

I have prepared a few examples on the [examples](https://github.com/TheLastBilly/libdirecpp/tree/master/examples) folder, so you can take a look in there to see a basic use case of the library. For a more detail explanation, you can look at the documentation at the [doc](https://github.com/TheLastBilly/libdirecpp/tree/master/doc) folder.

### Compiling examples

Just go to the folder where the exmaple is located, and type the following command to compile it:

```
g++ -ldirecpp main.cpp -o [name of the example]
```

Then, while inside that same directory, type `./[name of the example]` to run it.

## Resources
* [KISS (TNC)](https://en.wikipedia.org/wiki/KISS_(TNC))
* [AX.25 Link-Layer Protocol Specification](https://tapr.org/pub_ax25.html)
* [The KISS TNC: A simple Host-to-TNC communications protocol](http://www.ax25.net/kiss.aspx)
* [Direwolf - ax25_pad.c](https://github.com/wb2osz/direwolf/blob/master/ax25_pad.c)
* [Dire Wolf User Guide](https://github.com/wb2osz/direwolf/blob/master/doc/User-Guide.pdf)
