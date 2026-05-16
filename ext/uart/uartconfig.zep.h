
extern zend_class_entry *uart_uartconfig_ce;

ZEPHIR_INIT_CLASS(Uart_UARTConfig);

PHP_METHOD(Uart_UARTConfig, setRaw);
PHP_METHOD(Uart_UARTConfig, setBaudRate);
PHP_METHOD(Uart_UARTConfig, setDataBits);
PHP_METHOD(Uart_UARTConfig, setStopBits);
PHP_METHOD(Uart_UARTConfig, setParity);
PHP_METHOD(Uart_UARTConfig, setFlowControl);
PHP_METHOD(Uart_UARTConfig, getAttributes);
PHP_METHOD(Uart_UARTConfig, setAttributes);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setraw, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setbaudrate, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, baud, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setdatabits, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setstopbits, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setparity, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, parity, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setflowcontrol, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flow, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_getattributes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_uart_uartconfig_setattributes, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fd, IS_LONG, 0)
	ZEND_ARG_INFO(0, attrs)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(uart_uartconfig_method_entry) {
	PHP_ME(Uart_UARTConfig, setRaw, arginfo_uart_uartconfig_setraw, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setBaudRate, arginfo_uart_uartconfig_setbaudrate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setDataBits, arginfo_uart_uartconfig_setdatabits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setStopBits, arginfo_uart_uartconfig_setstopbits, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setParity, arginfo_uart_uartconfig_setparity, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setFlowControl, arginfo_uart_uartconfig_setflowcontrol, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, getAttributes, arginfo_uart_uartconfig_getattributes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Uart_UARTConfig, setAttributes, arginfo_uart_uartconfig_setattributes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
