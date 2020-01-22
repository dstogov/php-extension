/* test extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_test.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(test)

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("test.scale", "1", PHP_INI_ALL, OnUpdateLong, scale,
		zend_test_globals, test_globals)
PHP_INI_END()

/* {{{ void test_test1()
 */
PHP_FUNCTION(test_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "test");
}
/* }}} */

/* {{{ string test_test2( [ string $var ] )
 */
PHP_FUNCTION(test_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

PHP_FUNCTION(test_scale)
{
	double x;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_DOUBLE(x)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_DOUBLE(x * TEST_G(scale));
}

static PHP_GINIT_FUNCTION(test)
{
#if defined(COMPILE_DL_BCMATH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	test_globals->scale= 1;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(test)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(test)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "test support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_test_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_test_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

ZEND_BEGIN_ARG_INFO(arginfo_test_scale, 0)
	ZEND_ARG_INFO(0, x)
ZEND_END_ARG_INFO()

/* {{{ test_functions[]
 */
static const zend_function_entry test_functions[] = {
	PHP_FE(test_test1,		arginfo_test_test1)
	PHP_FE(test_test2,		arginfo_test_test2)
	PHP_FE(test_scale,		arginfo_test_scale)
	PHP_FE_END
};
/* }}} */

/* {{{ test_module_entry
 */
zend_module_entry test_module_entry = {
	STANDARD_MODULE_HEADER,
	"test",					/* Extension name */
	test_functions,			/* zend_function_entry */
	PHP_MINIT(test),				/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	NULL,							/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(test),			/* PHP_MINFO - Module info */
	PHP_TEST_VERSION,		/* Version */
	PHP_MODULE_GLOBALS(test),	/* Module globals */
	PHP_GINIT(test),			/* PHP_GINIT - Globals initialization */
	NULL,					/* PHP_GSHUTDOWN - Globals shutdown */
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_TEST
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(test)
#endif
