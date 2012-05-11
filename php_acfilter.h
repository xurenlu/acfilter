/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 226204 2007-01-01 19:32:10Z iliaa $ */
#ifndef PHP_ACFILTER_H
#define PHP_ACFILTER_H

extern zend_module_entry acfilter_module_entry;
#define phpext_acfilter_ptr &acfilter_module_entry

#ifdef PHP_WIN32
#define PHP_ACFILTER_API __declspec(dllexport)
#else
#define PHP_ACFILTER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(acfilter);
PHP_MSHUTDOWN_FUNCTION(acfilter);
PHP_RINIT_FUNCTION(acfilter);
PHP_RSHUTDOWN_FUNCTION(acfilter);
PHP_MINFO_FUNCTION(acfilter);

PHP_FUNCTION(confirm_acfilter_compiled);	/* For testing, remove later. */
PHP_FUNCTION(acfilter_new);
PHP_FUNCTION(acfilter_load_dict);
PHP_FUNCTION(acfilter_add_word);
PHP_FUNCTION(acfilter_prepare);
PHP_FUNCTION(acfilter_check_text);
PHP_FUNCTION(acfilter_close);
PHP_FUNCTION(array_experiments);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(acfilter)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(acfilter)
*/

/* In every utility function you add that needs to use variables 
   in php_acfilter_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as ACFILTER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define ACFILTER_G(v) TSRMG(acfilter_globals_id, zend_acfilter_globals *, v)
#else
#define ACFILTER_G(v) (acfilter_globals.v)
#endif

#endif	/* PHP_ACFILTER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
