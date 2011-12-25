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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_acfilter.h"

#include "mem_collector.h"
#include "acseg_tree.h"
#define DD printf("debug:%d %s\n",__LINE__,__FILE__);

/* If you declare any globals in php_acfilter.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(acfilter)
*/

/* True global resources - no need for thread safety here */
static int le_acfilter;
#define le_acfilter_name "Acfilter Index"
/* {{{ acfilter_functions[]
 *
 * Every user visible function must have an entry in acfilter_functions[].
 */
zend_function_entry acfilter_functions[] = {
	PHP_FE(confirm_acfilter_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(acfilter_new,	NULL)
	PHP_FE(acfilter_load_dict,	NULL)
	PHP_FE(acfilter_add_word,	NULL)
	PHP_FE(acfilter_prepare,	NULL)
	PHP_FE(acfilter_check_text,	NULL)
	PHP_FE(acfilter_close,	NULL)
	//PHP_FE(array_experiments,NULL)
	{NULL, NULL, NULL}	/* Must be the last line in acfilter_functions[] */
};
/* }}} */

/* {{{ acfilter_module_entry
 */
zend_module_entry acfilter_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"acfilter",
	acfilter_functions,
	PHP_MINIT(acfilter),
	PHP_MSHUTDOWN(acfilter),
	PHP_RINIT(acfilter),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(acfilter),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(acfilter),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ACFILTER
ZEND_GET_MODULE(acfilter)
#endif

static void acfilter_destructor_acindex(zend_rsrc_list_entry *rsrc TSRMLS_DC){
	acseg_index_t * acseg_index;
	acseg_index = (acseg_index_t * )rsrc->ptr;
	if(acseg_index)
		acseg_destory_index(&acseg_index);
}
/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("acfilter.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_acfilter_globals, acfilter_globals)
    STD_PHP_INI_ENTRY("acfilter.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_acfilter_globals, acfilter_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_acfilter_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_acfilter_init_globals(zend_acfilter_globals *acfilter_globals)
{
	acfilter_globals->global_value = 0;
	acfilter_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(acfilter)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	 le_acfilter= zend_register_list_destructors_ex(acfilter_destructor_acindex,NULL,le_acfilter_name,module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(acfilter)
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
PHP_RINIT_FUNCTION(acfilter)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(acfilter)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(acfilter)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "acfilter support", "enabled");
	php_info_print_table_row(2, "acfilter version", "1.0.0");
	php_info_print_table_row(2, "acfilter author", "162cm");
	php_info_print_table_row(2, "acfilter homepage", "http://www.162cm.com/");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_acfilter_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_acfilter_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "acfilter", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto resource acfilter_new()
    */
PHP_FUNCTION(acfilter_new)
{
	if (ZEND_NUM_ARGS() != 0) {
		WRONG_PARAM_COUNT;
	}
	//php_error(E_WARNING, "acfilter_new: not yet implemented");
	acseg_index_t * acseg_index;
	acseg_index = acseg_index_init();
	ZEND_REGISTER_RESOURCE(return_value,acseg_index,le_acfilter);
}
/* }}} */

/* {{{ proto  acfilter_load_dict(resource acindex, string dict_file_path)
    */
PHP_FUNCTION(acfilter_load_dict)
{
	char *dict_file_path = NULL;
	int argc = ZEND_NUM_ARGS();
	int acindex_id = -1;
	int dict_file_path_len;
	zval *acindex = NULL;
	acseg_index_t * acseg_index;
	if (zend_parse_parameters(argc TSRMLS_CC, "rs", &acindex, &dict_file_path, &dict_file_path_len) == FAILURE) {
		php_error(E_WARNING,"acfilter_load_dict :wrong number of parameters ");
		RETURN_FALSE;
	}

	if (acindex) {
		ZEND_FETCH_RESOURCE(acseg_index, acseg_index_t *, &acindex,acindex_id,le_acfilter_name, le_acfilter);
	}
	else{
		php_error(E_WARNING,"acfilter_load_dict got an invalid resource as first parameter");
		RETURN_FALSE;
	}
	acseg_index=acseg_index_load(acseg_index,dict_file_path);
	if(acseg_index ==NULL){
		php_error(E_WARNING,"acfilter_load_dict failed");
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto  acfilter_add_word(resource acindex, string word)
    */
PHP_FUNCTION(acfilter_add_word)
{
	char *word = NULL;
	int argc = ZEND_NUM_ARGS();
	int acindex_id = -1;
	int word_len;
	zval *acindex = NULL;
	acseg_index_t * acseg_index;

	if (zend_parse_parameters(argc TSRMLS_CC, "rs", &acindex, &word, &word_len) == FAILURE) 
		return;

	if (acindex) {
		ZEND_FETCH_RESOURCE(acseg_index, acseg_index_t *, &acindex,acindex_id,le_acfilter_name, le_acfilter);
	}
	if(word_len==0){
		RETURN_TRUE;
		return;
	}
	acseg_str_t  phrase;
	phrase.data=word;
	phrase.len=word_len;

	acseg_index=acseg_index_add(acseg_index,&phrase);
	if(acseg_index ==NULL){
		php_error(E_WARNING,"acfilter_load_dict failed");
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto  acfilter_prepare(resource acindex)
    */
PHP_FUNCTION(acfilter_prepare)
{
	int argc = ZEND_NUM_ARGS();
	int acindex_id = -1;
	zval *acindex = NULL;
	acseg_index_t * acseg_index;
	if (zend_parse_parameters(argc TSRMLS_CC, "r", &acindex) == FAILURE) {
		WRONG_PARAM_COUNT;
		RETURN_FALSE;
	}
	if (acindex) {
		ZEND_FETCH_RESOURCE(acseg_index, acseg_index_t *, &acindex,acindex_id,le_acfilter_name, le_acfilter);
	}
	acseg_index_fix(acseg_index);	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string acfilter_check_text(resource acindex, string text)
    */
PHP_FUNCTION(acfilter_check_text)
{
	char *text = NULL;
	int argc = ZEND_NUM_ARGS();
	int acindex_id = -1;
	int text_len;
	zval *acindex = NULL;
	acseg_index_t * acseg_index;

	if (zend_parse_parameters(argc TSRMLS_CC, "rs", &acindex, &text, &text_len) == FAILURE) 
		return;

	if (acindex) {
		ZEND_FETCH_RESOURCE(acseg_index, acseg_index_t *, &acindex,acindex_id,le_acfilter_name, le_acfilter);
	}

	acseg_result_t * seg_result;
	acseg_str_t acseg_text;
	acseg_text.data=text;
	acseg_text.len=text_len;
	seg_result = acseg_full_seg(acseg_index, &acseg_text);
	acseg_str_t *phrase;
	acseg_list_item_t *result_item;
	result_item = seg_result->list->first;

	char * ret;
	ret=malloc(sizeof(char)*2*text_len);
	bzero(ret,sizeof(char)*2*text_len);
	if(!ret){
		php_error(E_ERROR,"acfilter:can't alloc enough memory");
	}
	while (result_item) {
		phrase = (acseg_str_t *) result_item->data; 
		result_item = result_item->next;
		strncat(ret,phrase->data,phrase->len);
		strcat(ret,"|");
	}
	acseg_destory_result(&seg_result);
	//RETURN_TRUE;
	RETURN_STRING(ret,1);
}
/* }}} */

/* {{{ proto  acfilter_close(resource acindex)
    */
PHP_FUNCTION(acfilter_close)
{
	int argc = ZEND_NUM_ARGS();
	int acindex_id = -1;
	zval *acindex = NULL;
	acseg_index_t * acseg_index;

	if (zend_parse_parameters(argc TSRMLS_CC, "r", &acindex) == FAILURE) 
		return;

	if (acindex) {
		ZEND_FETCH_RESOURCE(acseg_index, acseg_index_t *, &acindex,acindex_id,le_acfilter_name, le_acfilter);
	}
	RETURN_BOOL(zend_list_delete(Z_LVAL_P(acindex)) == SUCCESS);
	RETURN_TRUE;
}
/* }}} */

PHP_FUNCTION(array_experiments) 
{ 
   zval *new_element;

   MAKE_STD_ZVAL(new_element);

   array_init(return_value);

   ZVAL_LONG(new_element, 10); 
   zend_hash_index_update(HASH_OF(return_value), 3, (void *)&new_element, sizeof(zval *), NULL); 
   add_next_index_long(return_value, 20); 
}
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
