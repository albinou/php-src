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

/* {{{ proto bool is_sqli(string arg)
   Return true if the arg user-input looks like an SQL injection */
PHP_FUNCTION(is_sqli)
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

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sqlidetector)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sqlidetector)
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
	PHP_FE(is_sqli, NULL)
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
	NULL,
	NULL,
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
