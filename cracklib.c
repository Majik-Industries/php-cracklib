/* cracklib extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_cracklib.h"

#define CRACKLIB_OK "Password OK"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ string cracklib_check( [ string $var ] )
 */
PHP_FUNCTION(cracklib_check)
{

    char *msg = NULL;
	char *passwd = NULL;
	size_t passwd_len = 0;



    char *dict = NULL;
    size_t dict_len = 0;
    char *user = "root";
    size_t user_len = sizeof("root") - 1;
    char *gecos = NULL;
    size_t gecos_len = 0;
    zval *retval;

    dict = (char *)GetDefaultCracklibDict();
    dict_len = strlen(dict);

	ZEND_PARSE_PARAMETERS_START(1, 4)
		Z_PARAM_STRING(passwd, passwd_len)
        Z_PARAM_OPTIONAL
		Z_PARAM_STRING(user, user_len)
		Z_PARAM_STRING(gecos, gecos_len)
		Z_PARAM_STRING(dict, dict_len)
	ZEND_PARSE_PARAMETERS_END();

    /* Allocate local variables that are returned */
    retval = (zval *)malloc(sizeof(zval));

    /* Return value is an associative array
        $retval = array("ok" => bool, "reason" = NULL|string);

    */
    array_init_size(retval, 2);


    if ((msg = (char *)FascistCheckUser(passwd, dict, user, gecos)) == NULL) {
        add_assoc_bool(retval, "ok", 1);
        add_assoc_stringl(retval, "reason", CRACKLIB_OK, strlen(CRACKLIB_OK));
    } else {
        add_assoc_bool(retval, "ok", 0);
        add_assoc_stringl(retval, "reason", msg, strlen(msg));
    }
	RETURN_ARR(Z_ARR_P(retval));
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cracklib)
{
#if defined(ZTS) && defined(COMPILE_DL_CRACKLIB)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cracklib)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cracklib support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_cracklib_check, 0)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ cracklib_functions[]
 */
static const zend_function_entry cracklib_functions[] = {
	PHP_FE(cracklib_check,		arginfo_cracklib_check)
	PHP_FE_END
};
/* }}} */

/* {{{ cracklib_module_entry
 */
zend_module_entry cracklib_module_entry = {
	STANDARD_MODULE_HEADER,
	"cracklib",					/* Extension name */
	cracklib_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(cracklib),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(cracklib),			/* PHP_MINFO - Module info */
	PHP_CRACKLIB_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CRACKLIB
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(cracklib)
#endif

