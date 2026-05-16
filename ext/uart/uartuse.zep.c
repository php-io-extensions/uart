
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
#include "kernel/string.h"
#include "kernel/memory.h"
#include "api/uart-use.h"
#include "kernel/operators.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Uart_UARTUse)
{
	ZEPHIR_REGISTER_CLASS(Uart, UARTUse, uart, uartuse, uart_uartuse_method_entry, 0);

	return SUCCESS;
}

/**
 * Read up to bytes_to_read bytes from the UART device.
 * Blocks until data is available (behaviour controlled by VMIN/VTIME set via UARTConfig).
 * @param int fd File descriptor
 * @param int bytes_to_read Maximum number of bytes to read
 * @return string Data read as a binary string, or "" on error
 */
PHP_METHOD(Uart_UARTUse, read)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *fd_param = NULL, *bytes_to_read_param = NULL, result, _0, _1;
	zend_long fd, bytes_to_read;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(bytes_to_read)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &fd_param, &bytes_to_read_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bytes_to_read);
	ZEPHIR_INIT_VAR(&result);
	uart_read(&result, &_0, &_1);
	RETURN_CCTOR(&result);
}

/**
 * Write data to the UART device.
 * @param int fd File descriptor
 * @param var data Data string to transmit
 * @param int bytes_to_write Number of bytes to write
 * @return int Bytes written on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, write)
{
	zval payload;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *fd_param = NULL, *data = NULL, data_sub, *bytes_to_write_param = NULL, _0, _1;
	zend_long fd, bytes_to_write, result = 0;

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&payload);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(fd)
		Z_PARAM_ZVAL(data)
		Z_PARAM_LONG(bytes_to_write)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &fd_param, &data, &bytes_to_write_param);
	zephir_get_strval(&payload, data);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, bytes_to_write);
	result = uart_write(&_0, &payload, &_1);
	RETURN_MM_LONG(result);
}

/**
 * Block until all output written to fd has been physically transmitted.
 * @param int fd File descriptor
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, drain)
{
	zval *fd_param = NULL, _0;
	zend_long fd, result = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &fd_param);
	ZVAL_LONG(&_0, fd);
	result = uart_drain(&_0);
	RETURN_LONG(result);
}

/**
 * Discard queued data.
 * queue_selector: 0 = TCIFLUSH (input), 1 = TCOFLUSH (output), 2 = TCIOFLUSH (both).
 * @param int fd File descriptor
 * @param int queue_selector 0, 1, or 2
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, flush)
{
	zval *fd_param = NULL, *queue_selector_param = NULL, _0, _1;
	zend_long fd, queue_selector, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(queue_selector)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &queue_selector_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, queue_selector);
	result = uart_flush(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Suspend or resume data flow.
 * action: 0 = TCOOFF (suspend output), 1 = TCOON (resume output),
 *         2 = TCIOFF (suspend input), 3 = TCION (resume input).
 * @param int fd File descriptor
 * @param int action 0, 1, 2, or 3
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, flow)
{
	zval *fd_param = NULL, *action_param = NULL, _0, _1;
	zend_long fd, action, result = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(fd)
		Z_PARAM_LONG(action)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &fd_param, &action_param);
	ZVAL_LONG(&_0, fd);
	ZVAL_LONG(&_1, action);
	result = uart_flow(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Get modem control line status bitmask via TIOCMGET.
 * Compare against TIOCM_DTR (0x002), TIOCM_RTS (0x004), TIOCM_CTS (0x020), etc.
 * @param int fd File descriptor
 * @return int Modem status bitmask, or -1 on failure
 */
PHP_METHOD(Uart_UARTUse, getModemBits)
{
	zval *fd_param = NULL, _0;
	zend_long fd, result = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(fd)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &fd_param);
	ZVAL_LONG(&_0, fd);
	result = uart_get_modem_bits(&_0);
	RETURN_LONG(result);
}

/**
 * Replace the full modem control line state via TIOCMSET.
 * @param int fd File descriptor
 * @param int bits Bitmask of TIOCM_* flags
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, setModemBits)
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
	result = uart_set_modem_bits(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Assert (raise) specific modem control lines without affecting others, via TIOCMBIS.
 * @param int fd File descriptor
 * @param int bits Bitmask of TIOCM_* flags to raise
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, setBits)
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
	result = uart_set_bits(&_0, &_1);
	RETURN_LONG(result);
}

/**
 * Deassert (lower) specific modem control lines without affecting others, via TIOCMBIC.
 * @param int fd File descriptor
 * @param int bits Bitmask of TIOCM_* flags to lower
 * @return int 0 on success, -1 on failure
 */
PHP_METHOD(Uart_UARTUse, clearBits)
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
	result = uart_clear_bits(&_0, &_1);
	RETURN_LONG(result);
}

