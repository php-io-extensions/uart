
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "api/uart-config.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Uart_UARTConfig)
{
	ZEPHIR_REGISTER_CLASS(Uart, UARTConfig, uart, uartconfig, uart_uartconfig_method_entry, 0);

	return SUCCESS;
}

/**
 * Configure the terminal for raw I/O (no processing, no echo, no signals).
 * Calls cfmakeraw() then sets VMIN=1, VTIME=0: block until at least one byte arrives.
 * This is the correct starting point before setting baud rate and framing.
 * @param int fd File descriptor opened with Fd\FD::open()
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTConfig, setRaw)
{
	zval *fd_param = NULL, _0;
	zend_long fd, result = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &fd_param);
	ZVAL_LONG(&_0, fd);
	result = uart_set_raw(&_0);
	RETURN_LONG(result);
}

/**
 * Set baud rate (input and output simultaneously).
 * Supported on all platforms: 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800,
 * 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400.
 * Linux-only: 460800, 500000, 576000, 921600, 1000000, 1152000, 1500000,
 * 2000000, 2500000, 3000000, 3500000, 4000000.
 * @param int fd File descriptor
 * @param int baud Numeric baud rate (e.g. 9600, 115200)
 * @return int 0 on success, -1 on unrecognised rate or failure
 */
PHP_METHOD(Uart_UARTConfig, setBaudRate)
{
	zval *fd_param = NULL, *baud_param = NULL, _0, _1;
	zend_long fd, baud, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(baud)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &baud_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, baud);
	result = uart_set_baud_rate(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Set number of data bits per character (5, 6, 7, or 8).
 * @param int fd File descriptor
 * @param int bits 5, 6, 7, or 8
 * @return int 0 on success, -1 on invalid value or failure
 */
PHP_METHOD(Uart_UARTConfig, setDataBits)
{
	zval *fd_param = NULL, *bits_param = NULL, _0, _1;
	zend_long fd, bits, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(bits)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &bits_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bits);
	result = uart_set_data_bits(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Set number of stop bits (1 or 2).
 * @param int fd File descriptor
 * @param int bits 1 or 2
 * @return int 0 on success, -1 on invalid value or failure
 */
PHP_METHOD(Uart_UARTConfig, setStopBits)
{
	zval *fd_param = NULL, *bits_param = NULL, _0, _1;
	zend_long fd, bits, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(bits)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &bits_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bits);
	result = uart_set_stop_bits(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Set parity mode: 0 = none, 1 = even, 2 = odd.
 * @param int fd File descriptor
 * @param int parity 0 (none), 1 (even), or 2 (odd)
 * @return int 0 on success, -1 on invalid value or failure
 */
PHP_METHOD(Uart_UARTConfig, setParity)
{
	zval *fd_param = NULL, *parity_param = NULL, _0, _1;
	zend_long fd, parity, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(parity)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &parity_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, parity);
	result = uart_set_parity(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Set flow control mode: 0 = none, 1 = hardware (RTS/CTS), 2 = software (XON/XOFF).
 * @param int fd File descriptor
 * @param int flow 0 (none), 1 (hardware), or 2 (software)
 * @return int 0 on success, -1 on invalid value or failure
 */
PHP_METHOD(Uart_UARTConfig, setFlowControl)
{
	zval *fd_param = NULL, *flow_param = NULL, _0, _1;
	zend_long fd, flow, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(flow)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &flow_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, flow);
	result = uart_set_flow_control(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Read all current terminal attributes into an associative array.
 * Keys: iflag, oflag, cflag, lflag, ispeed, ospeed, cc (array indexed 0..NCCS-1).
 * Returns empty array on failure.
 * @param int fd File descriptor
 * @return array
 */
PHP_METHOD(Uart_UARTConfig, getAttributes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *fd_param = NULL, attrs, _0;
	zend_long fd;

	ZVAL_UNDEF(&attrs);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &fd_param);
	ZVAL_LONG(&_0, fd);
	ZEPHIR_INIT_VAR(&attrs);
	uart_get_attributes(&attrs, &_0);
	RETURN_CCTOR(&attrs);
}

/**
 * Apply terminal attributes from an associative array via tcsetattr(TCSANOW).
 * Accepts the same keys returned by getAttributes(). Partial updates are supported —
 * only keys present in $attrs are applied; the rest are read from the current state.
 * @param int fd File descriptor
 * @param array attrs Attribute array
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTConfig, setAttributes)
{
	zval *fd_param = NULL, *attrs = NULL, attrs_sub, _0;
	zend_long fd, result = 0;

	ZVAL_UNDEF(&attrs_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_ZVAL(attrs)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &attrs);
	ZVAL_LONG(&_0, fd);
	result = uart_set_attributes(&_0, attrs);
	RETURN_LONG(result);
}

