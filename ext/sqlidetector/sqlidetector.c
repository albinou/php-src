/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Albin Kauffmann <albin@kauff.org>                            |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sqlidetector.h"

#include "libinjection.h"
#include "libinjection_sqli.h"

/* If you declare any globals in php_sqlidetector.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(sqlidetector)
*/

/* True global resources - no need for thread safety here */
static int le_sqlidetector;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("sqlidetector.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_sqlidetector_globals, sqlidetector_globals)
    STD_PHP_INI_ENTRY("sqlidetector.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_sqlidetector_globals, sqlidetector_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_sqlidetector_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(sqli_check)
{
	struct libinjection_sqli_state state;
	char *arg = NULL;
	size_t arg_len, len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	libinjection_sqli_init(&state, arg, arg_len, FLAG_NONE);

	RETURN_BOOL(libinjection_is_sqli(&state));
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_sqlidetector_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_sqlidetector_init_globals(zend_sqlidetector_globals *sqlidetector_globals)
{
	sqlidetector_globals->global_value = 0;
	sqlidetector_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sqlidetector)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sqlidetector)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(sqlidetector)
{
#if defined(COMPILE_DL_SQLIDETECTOR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sqlidetector)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sqlidetector)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sqlidetector support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ sqlidetector_functions[]
 *
 * Every user visible function must have an entry in sqlidetector_functions[].
 */
const zend_function_entry sqlidetector_functions[] = {
	PHP_FE(sqli_check, NULL)
	PHP_FE_END
};
/* }}} */

/* {{{ sqlidetector_module_entry
 */
zend_module_entry sqlidetector_module_entry = {
	STANDARD_MODULE_HEADER,
	"sqlidetector",
	sqlidetector_functions,
	PHP_MINIT(sqlidetector),
	PHP_MSHUTDOWN(sqlidetector),
	PHP_RINIT(sqlidetector),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(sqlidetector),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(sqlidetector),
	PHP_SQLIDETECTOR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SQLIDETECTOR
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(sqlidetector)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
