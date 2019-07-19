#!/bin/sh

aclocal -I .
autoheader
libtoolize --automake
automake --foreign --add-missing
autoconf
