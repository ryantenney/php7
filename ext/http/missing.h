/*
    +--------------------------------------------------------------------+
    | PECL :: http                                                       |
    +--------------------------------------------------------------------+
    | Redistribution and use in source and binary forms, with or without |
    | modification, are permitted provided that the conditions mentioned |
    | in the accompanying LICENSE file are met.                          |
    +--------------------------------------------------------------------+
    | Copyright (c) 2004-2007, Michael Wallner <mike@php.net>            |
    +--------------------------------------------------------------------+
*/

/* $Id: missing.h 276977 2009-03-10 17:25:22Z mike $ */

#ifndef PHP_HTTP_MISSING
#define PHP_HTTP_MISSING

#include "php_version.h"

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION >= 3)
#	define HTTP_ZAPI_HASH_TSRMLS_CC TSRMLS_CC
#	define HTTP_ZAPI_HASH_TSRMLS_DC TSRMLS_DC
#	define HTTP_ZAPI_CONST_CAST(t) (const t)
#	define GLOBAL_ERROR_HANDLING EG(error_handling)
#	define GLOBAL_EXCEPTION_CLASS EG(exception_class)
#	define IS_CALLABLE(cb_zv, flags, cb_sp) zend_is_callable((cb_zv), (flags), (cb_sp) TSRMLS_CC)
#	define HTTP_STATIC_ARG_INFO
#else
#	define HTTP_ZAPI_HASH_TSRMLS_CC
#	define HTTP_ZAPI_HASH_TSRMLS_DC
#	define HTTP_ZAPI_CONST_CAST(t) (t)
#	define GLOBAL_ERROR_HANDLING PG(error_handling)
#	define GLOBAL_EXCEPTION_CLASS PG(exception_class)
#	define IS_CALLABLE(cb_zv, flags, cb_sp) zend_is_callable((cb_zv), (flags), (cb_sp))
#	define HTTP_STATIC_ARG_INFO static
#endif

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION == 0)
#	define WONKY
#endif

#ifndef pemalloc_rel
#	define pemalloc_rel(size, persistent) ((persistent)?malloc(size):emalloc_rel(size))
#endif

#ifndef ZEND_ACC_DEPRECATED
#	define ZEND_ACC_DEPRECATED 0
#endif

#if PHP_MAJOR_VERSION == 4 && PHP_MINOR_VERSION == 3 && PHP_RELEASE_VERSION < 10
#	define php_url_parse_ex(u, l) php_url_parse(u)
#endif

#ifndef TSRMLS_FETCH_FROM_CTX
#	ifdef ZTS
#		define TSRMLS_FETCH_FROM_CTX(ctx)	void ***tsrm_ls = (void ***) ctx
#	else
#		define TSRMLS_FETCH_FROM_CTX(ctx)
#	endif
#endif

#ifndef TSRMLS_SET_CTX
#	ifdef ZTS
#		define TSRMLS_SET_CTX(ctx)	ctx = (void ***) tsrm_ls
#	else
#		define TSRMLS_SET_CTX(ctx)
#	endif
#endif

#ifndef ZVAL_ADDREF
#	define ZVAL_ADDREF Z_ADDREF_P
#endif

#ifndef SEPARATE_ARG_IF_REF
#define SEPARATE_ARG_IF_REF(zv) \
	if (PZVAL_IS_REF(zv)) { \
		zval *ov = zv; \
		ALLOC_INIT_ZVAL(zv); \
		Z_TYPE_P(zv) = Z_TYPE_P(ov); \
		zv->value = ov->value; \
		zval_copy_ctor(zv); \
	} else { \
		ZVAL_ADDREF(zv); \
	}
#endif

#ifndef ZVAL_ZVAL
#define ZVAL_ZVAL(z, zv, copy, dtor) {  \
		int is_ref, refcount;           \
		is_ref = (z)->is_ref;           \
		refcount = (z)->refcount;       \
		*(z) = *(zv);                   \
		if (copy) {                     \
			zval_copy_ctor(z);          \
	    }                               \
		if (dtor) {                     \
			if (!copy) {                \
				ZVAL_NULL(zv);          \
			}                           \
			zval_ptr_dtor(&zv);         \
	    }                               \
		(z)->is_ref = is_ref;           \
		(z)->refcount = refcount;       \
	}
#endif
#ifndef RETVAL_ZVAL
#	define RETVAL_ZVAL(zv, copy, dtor)		ZVAL_ZVAL(return_value, zv, copy, dtor)
#endif
#ifndef RETURN_ZVAL
#	define RETURN_ZVAL(zv, copy, dtor)		{ RETVAL_ZVAL(zv, copy, dtor); return; }
#endif

#ifndef ZEND_MN
#	define ZEND_MN(name) ZEND_FN(name)
#endif

#ifdef WONKY
extern int zend_declare_property_double(zend_class_entry *ce, char *name, int name_length, double value, int access_type TSRMLS_DC);
extern void zend_update_property_double(zend_class_entry *scope, zval *object, char *name, int name_length, double value TSRMLS_DC);

extern int zend_declare_property_bool(zend_class_entry *ce, char *name, int name_length, long value, int access_type TSRMLS_DC);
extern void zend_update_property_bool(zend_class_entry *scope, zval *object, char *name, int name_length, long value TSRMLS_DC);

extern void zend_update_property_stringl(zend_class_entry *scope, zval *object, char *name, int name_length, char *value, int value_len TSRMLS_DC);
#endif

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

