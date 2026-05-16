
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "uart.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *uart_uartconfig_ce;
zend_class_entry *uart_uartuse_ce;

ZEND_DECLARE_MODULE_GLOBALS(uart)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(uart)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Uart_UARTConfig);
	ZEPHIR_INIT(Uart_UARTUse);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(uart)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_uart_globals *uart_globals)
{
	uart_globals->initialized = 0;

	/* Cache Enabled */
	uart_globals->cache_enabled = 1;

	/* Recursive Lock */
	uart_globals->recursive_lock = 0;

	/* Static cache */
	memset(uart_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_uart_globals *uart_globals)
{
	
}

static PHP_RINIT_FUNCTION(uart)
{
	zend_uart_globals *uart_globals_ptr;
	uart_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(uart_globals_ptr);
	zephir_initialize_memory(uart_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(uart)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(uart)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_UART_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_UART_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_UART_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_UART_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_UART_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(uart)
{
#if defined(COMPILE_DL_UART) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(uart_globals);
	php_zephir_init_module_globals(uart_globals);
}

static PHP_GSHUTDOWN_FUNCTION(uart)
{
	
}


zend_function_entry php_uart_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_uart_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry uart_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_uart_deps,
	PHP_UART_EXTNAME,
	php_uart_functions,
	PHP_MINIT(uart),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(uart),
#else
	NULL,
#endif
	PHP_RINIT(uart),
	PHP_RSHUTDOWN(uart),
	PHP_MINFO(uart),
	PHP_UART_VERSION,
	ZEND_MODULE_GLOBALS(uart),
	PHP_GINIT(uart),
	PHP_GSHUTDOWN(uart),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(uart),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_UART
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(uart)
#endif
