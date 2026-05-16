
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_UART_H
#define PHP_UART_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_UART_NAME        "uart"
#define PHP_UART_VERSION     "0.1.0"
#define PHP_UART_EXTNAME     "uart"
#define PHP_UART_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_UART_ZEPVERSION  "0.19.0-$Id$"
#define PHP_UART_DESCRIPTION "PHP-Controllable UART Extension"



ZEND_BEGIN_MODULE_GLOBALS(uart)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(uart)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(uart)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(uart, v)
#else
	#define ZEPHIR_GLOBAL(v) (uart_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_uart_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(uart_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(uart_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def uart_globals
#define zend_zephir_globals_def zend_uart_globals

extern zend_module_entry uart_module_entry;
#define phpext_uart_ptr &uart_module_entry

#endif
