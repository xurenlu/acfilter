dnl $Id$
dnl config.m4 for extension acfilter

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(acfilter, for acfilter support,
dnl Make sure that the comment is aligned:
dnl [  --with-acfilter             Include acfilter support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(acfilter, whether to enable acfilter support,
dnl Make sure that the comment is aligned:
[  --enable-acfilter           Enable acfilter support])

if test "$PHP_ACFILTER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-acfilter -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/acfilter.h"  # you most likely want to change this
  dnl if test -r $PHP_ACFILTER/$SEARCH_FOR; then # path given as parameter
  dnl   ACFILTER_DIR=$PHP_ACFILTER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for acfilter files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ACFILTER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ACFILTER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the acfilter distribution])
  dnl fi

  dnl # --with-acfilter -> add include path
  dnl PHP_ADD_INCLUDE($ACFILTER_DIR/include)

  dnl # --with-acfilter -> check for lib and symbol presence
  dnl LIBNAME=acfilter # you may want to change this
  dnl LIBSYMBOL=acfilter # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ACFILTER_DIR/lib, ACFILTER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ACFILTERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong acfilter lib version or lib not found])
  dnl ],[
  dnl   -L$ACFILTER_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(ACFILTER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(acfilter,  acfilter.c  acseg_rbtree.c  acseg_tree.c  acseg_util.c  exists.c  mem_collector.c , $ext_shared)
fi
