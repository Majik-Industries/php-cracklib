PHP_ARG_WITH(crack, for crack support,
[  --with-crack[=DIR]       Include crack support])

if test "$PHP_CRACK" != "no"; then
  for i in $PHP_CRACK /usr/local /usr; do
    test -f $i/include/crack.h && CRACK_DIR=$i && break
  done

  if test -z "$CRACK_DIR"; then
    AC_MSG_ERROR(crack.h not found. Please reinstall libcrack.)
  fi

  PHP_CHECK_LIBRARY(crack, FascistCheck,
  [
    PHP_ADD_LIBRARY(ltdl,, CRACK_SHARED_LIBADD)
    AC_DEFINE(HAVE_LIBCRACK,1,[ ])
  ],[
    PHP_CHECK_LIBRARY(crack, FascistCheck,
    [
      AC_DEFINE(HAVE_LIBCRACK,1,[ ])
    ],[
      AC_MSG_ERROR([Sorry, I was not able to diagnose which libcrack version you have installed.])
    ],[
      -L$CRACK_DIR/$PHP_LIBDIR
    ])
  ],[
    -L$CRACK_DIR/$PHP_LIBDIR -lltdl
  ])

  PHP_ADD_LIBRARY_WITH_PATH(crack, $CRACK_DIR/$PHP_LIBDIR, CRACK_SHARED_LIBADD)
  PHP_ADD_INCLUDE($CRACK_DIR/include)

  PHP_SUBST(CRACK_SHARED_LIBADD)
  PHP_NEW_EXTENSION(crack, crack.c, $ext_shared,,)
fi

