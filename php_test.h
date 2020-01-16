/* test extension for PHP */

#ifndef PHP_TEST_H
# define PHP_TEST_H

extern zend_module_entry test_module_entry;
# define phpext_test_ptr &test_module_entry

# define PHP_TEST_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TEST)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TEST_H */
