dnl $Id$
dnl config.m4 for extension sqlidetector

PHP_ARG_ENABLE(sqlidetector, whether to enable sqlidetector support,
[  --enable-sqlidetector           Enable sqlidetector support])

if test "$PHP_SQLIDETECTOR" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sqlidetector -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sqlidetector.h"  # you most likely want to change this
  dnl if test -r $PHP_SQLIDETECTOR/$SEARCH_FOR; then # path given as parameter
  dnl   SQLIDETECTOR_DIR=$PHP_SQLIDETECTOR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sqlidetector files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SQLIDETECTOR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SQLIDETECTOR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sqlidetector distribution])
  dnl fi

  dnl # --with-sqlidetector -> add include path
  dnl PHP_ADD_INCLUDE($SQLIDETECTOR_DIR/include)

  dnl # --with-sqlidetector -> check for lib and symbol presence
  dnl LIBNAME=sqlidetector # you may want to change this
  dnl LIBSYMBOL=sqlidetector # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SQLIDETECTOR_DIR/$PHP_LIBDIR, SQLIDETECTOR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SQLIDETECTORLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sqlidetector lib version or lib not found])
  dnl ],[
  dnl   -L$SQLIDETECTOR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SQLIDETECTOR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sqlidetector, sqlidetector.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
