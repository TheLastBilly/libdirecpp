#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(libdirecpp, 0.1.2, jtmonegro@gmail.com)
AM_INIT_AUTOMAKE(libdirecpp, 0.1.2)

AC_CONFIG_SRCDIR(src/direcpp.cpp)
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/socket.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
LT_INIT

# Checks for library functions.
AC_CHECK_FUNCS([bzero memset socket strerror])

AC_OUTPUT(Makefile src/Makefile)
