dnl $Id$
dnl config.m4 for extension sqlidetector

PHP_ARG_ENABLE(sqlidetector, whether to enable sqlidetector support,
[  --enable-sqlidetector           Enable sqlidetector support])

if test "$PHP_SQLIDETECTOR" != "no"; then
  dnl Write more examples of tests here...

  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/libinjection.h"  # you most likely want to change this
  AC_MSG_CHECKING([for libinjection files in default path])
  for i in $SEARCH_PATH ; do
    if test -r $i/$SEARCH_FOR; then
      LIBINJECTION_DIR=$i
      AC_MSG_RESULT(found in $i)
    fi
  done

  if test -z "$LIBINJECTION_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the libinjection distribution from https://github.com/client9/libinjection])
  fi

  PHP_ADD_INCLUDE($LIBINJECTION_DIR/include)

  PHP_CHECK_LIBRARY(injection,libinjection_sqli_init,
  [
    PHP_ADD_LIBRARY_WITH_PATH(injection, $LIBINJECTION_DIR/$PHP_LIBDIR, LIBINJECTION_SHARED_LIBADD)
    AC_DEFINE(HAVE_LIBINJECTION,1,[ ])
  ],[
    AC_MSG_ERROR([wrong injection lib version or lib not found])
  ],[
    -L$LIBINJECTION_DIR/$PHP_LIBDIR -lm
  ])

  PHP_NEW_EXTENSION(sqlidetector, sqlidetector.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
