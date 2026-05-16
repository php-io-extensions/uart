#ifndef PHP_UART_CONFIG_API_H
#define PHP_UART_CONFIG_API_H

#include "php.h"

zend_long uart_set_raw(zval *fd);
zend_long uart_set_baud_rate(zval *fd, zval *baud);
zend_long uart_set_data_bits(zval *fd, zval *bits);
zend_long uart_set_stop_bits(zval *fd, zval *bits);
zend_long uart_set_parity(zval *fd, zval *parity);
zend_long uart_set_flow_control(zval *fd, zval *flow);
void      uart_get_attributes(zval *return_value, zval *fd);
zend_long uart_set_attributes(zval *fd, zval *attrs);

#endif /* PHP_UART_CONFIG_API_H */
