/* test extension for PHP */

#ifndef PHP_TEST_H
# define PHP_TEST_H

extern zend_module_entry test_module_entry;
# define phpext_test_ptr &test_module_entry

# define PHP_TEST_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TEST)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

ZEND_BEGIN_MODULE_GLOBALS(test)
	zend_long scale;
ZEND_END_MODULE_GLOBALS(test)

ZEND_EXTERN_MODULE_GLOBALS(test)

#define TEST_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(test, v)

#endif	/* PHP_TEST_H */
