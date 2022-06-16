/* crack extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_crack.h"

#define CRACK_OK "Password OK"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ string crack_check( [ string $var ] )
 */
PHP_FUNCTION(crack_check)
{

    char *msg = NULL;
	char *passwd = NULL;
	size_t passwd_len = 0;



    char *db = NULL;
    size_t db_len = 0;
    char *user = "root";
    size_t user_len = sizeof("root") - 1;
    char *gecos = NULL;
    size_t gecos_len = 0;
    zval ok;

    db = GetDefaultCracklibDict();
    db_len = strlen(db);

    /* Default to a valid password */
    ZVAL_TRUE(ok);

    /* Return value is an associative array
        $retval = array("ok" => bool, "reason" = NULL|string);

    */
    array_init(retval);

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_STRING(passwd, passwd_len)
        Z_PARAM_OPTIONAL
		Z_PARAM_STRING(db, db_len)
		Z_PARAM_STRING(user, user_len)
		Z_PARAM_STRING(gecos, gecos_len)
	ZEND_PARSE_PARAMETERS_END();



    if ((msg = FascistCheckUser(passwd, dict, user, gecos)) == NULL) {
        add_assoc_str(retval, "ok", ok ,0);
        add_assoc_str(retval, "reason", zend_string_init(CRACK_OK, strlen(CRACK_OK)) ,0);
    } else {
        ZVAL_TRUE(ok);
        add_assoc_str(retval, "ok", ok ,0);
        add_assoc_str(retval, "reason", zend_string_init(msg, strlen(msg)) ,0);
    }
	RETURN_ARRAY(retval);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(crack)
{
#if defined(ZTS) && defined(COMPILE_DL_CRACK)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(crack)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "crack support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_crack_check, 0)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(1, str)
	ZEND_ARG_INFO(2, str)
	ZEND_ARG_INFO(3, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ crack_functions[]
 */
static const zend_function_entry crack_functions[] = {
	PHP_FE(crack_check,		arginfo_crack_check)
	PHP_FE_END
};
/* }}} */

/* {{{ crack_module_entry
 */
zend_module_entry crack_module_entry = {
	STANDARD_MODULE_HEADER,
	"crack",					/* Extension name */
	crack_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(crack),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(crack),			/* PHP_MINFO - Module info */
	PHP_CRACK_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CRACK
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(crack)
#endif

