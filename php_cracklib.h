/* crack extension for PHP */

#ifndef PHP_CRACKLIB_H
# define PHP_CRACKLIB_H
#include <crack.h>

extern zend_module_entry crack_module_entry;
# define phpext_crack_ptr &crack_module_entry

# define PHP_CRACKLIB_VERSION "1.0"

# if defined(ZTS) && defined(COMPILE_DL_CRACKLIB)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_CRACKLIB_H */

