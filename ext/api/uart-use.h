#ifndef PHP_UART_USE_API_H
#define PHP_UART_USE_API_H

#include "php.h"

void      uart_read(zval *return_value, zval *fd, zval *bytes_to_read);
zend_long uart_write(zval *fd, zval *data, zval *bytes_to_write);
zend_long uart_drain(zval *fd);
zend_long uart_flush(zval *fd, zval *queue_selector);
zend_long uart_flow(zval *fd, zval *action);
zend_long uart_get_modem_bits(zval *fd);
zend_long uart_set_modem_bits(zval *fd, zval *bits);
zend_long uart_set_bits(zval *fd, zval *bits);
zend_long uart_clear_bits(zval *fd, zval *bits);

#endif /* PHP_UART_USE_API_H */
