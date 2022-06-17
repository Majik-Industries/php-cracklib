PHP_ARG_WITH(cracklib, for cracklib support,
[  --with-cracklib[=DIR]       Include cracklib support])

if test "$PHP_CRACKLIB" != "no"; then
  for i in $PHP_CRACKLIB /usr/local /usr; do
    test -f $i/include/crack.h && CRACKLIB_DIR=$i && break
  done

  if test -z "$CRACKLIB_DIR"; then
    AC_MSG_ERROR(crack.h not found. Please reinstall libcrack.)
  fi

  PHP_CHECK_LIBRARY(crack, FascistCheck,
  [
    PHP_ADD_LIBRARY(ltdl,, CRACKLIB_SHARED_LIBADD)
    AC_DEFINE(HAVE_LIBCRACK,1,[ ])
  ],[
    PHP_CHECK_LIBRARY(crack, FascistCheck,
    [
      AC_DEFINE(HAVE_LIBCRACK,1,[ ])
    ],[
      AC_MSG_ERROR([Sorry, I was not able to diagnose which libcrack version you have installed.])
    ],[
      -L$CRACKLIB_DIR/$PHP_LIBDIR
    ])
  ],[
    -L$CRACKLIB_DIR/$PHP_LIBDIR -lltdl
  ])

  PHP_ADD_LIBRARY_WITH_PATH(cracklib, $CRACKLIB_DIR/$PHP_LIBDIR, CRACKLIB_SHARED_LIBADD)
  PHP_ADD_INCLUDE($CRACKLIB_DIR/include)

  PHP_SUBST(CRACKLIB_SHARED_LIBADD)
  PHP_NEW_EXTENSION(cracklib, cracklib.c, $ext_shared,,)
fi

