
extern zend_class_entry *uart_uartuse_ce;

ZEPHIR_INIT_CLASS(Uart_UARTUse);

PHP_METHOD(Uart_UARTUse, read);
PHP_METHOD(Uart_UARTUse, write);
PHP_METHOD(Uart_UARTUse, drain);
PHP_METHOD(Uart_UARTUse, flush);
PHP_METHOD(Uart_UARTUse, flow);
PHP_METHOD(Uart_UARTUse, getModemBits);
PHP_METHOD(Uart_UARTUse, setModemBits);
PHP_METHOD(Uart_UARTUse, setBits);
PHP_METHOD(Uart_UARTUse, clearBits);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_read, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytes_to_read, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_write, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_TYPE_INFO(0, bytes_to_write, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_drain, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_flush, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queue_selector, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_flow, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, action, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_getmodembits, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_setmodembits, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_setbits, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartuse_clearbits, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(uart_uartuse_method_entry) {
	PHP_ME(Uart_UARTUse, read, arginfo_uart_uartuse_read, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, write, arginfo_uart_uartuse_write, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, drain, arginfo_uart_uartuse_drain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, flush, arginfo_uart_uartuse_flush, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, flow, arginfo_uart_uartuse_flow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, getModemBits, arginfo_uart_uartuse_getmodembits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, setModemBits, arginfo_uart_uartuse_setmodembits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, setBits, arginfo_uart_uartuse_setbits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTUse, clearBits, arginfo_uart_uartuse_clearbits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
