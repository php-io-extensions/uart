#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "uart-use.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

void uart_read(zval *return_value, zval *fd, zval *bytes_to_read)
{
    size_t n = (size_t) Z_LVAL_P(bytes_to_read);
    char *buf = emalloc(n + 1);
    ssize_t read_n = read((int) Z_LVAL_P(fd), buf, n);

    if (read_n < 0) {
        efree(buf);
        ZVAL_EMPTY_STRING(return_value);
    } else {
        buf[read_n] = '\0';
        ZVAL_STRINGL(return_value, buf, (size_t) read_n);
        efree(buf);
    }
}

zend_long uart_write(zval *fd, zval *data, zval *bytes_to_write)
{
    return (zend_long) write(
        (int)      Z_LVAL_P(fd),
        (uint8_t*) Z_STRVAL_P(data),
        (size_t)   Z_LVAL_P(bytes_to_write)
    );
}

zend_long uart_drain(zval *fd)
{
    return (zend_long) tcdrain((int) Z_LVAL_P(fd));
}

zend_long uart_flush(zval *fd, zval *queue_selector)
{
    return (zend_long) tcflush((int) Z_LVAL_P(fd), (int) Z_LVAL_P(queue_selector));
}

zend_long uart_flow(zval *fd, zval *action)
{
    return (zend_long) tcflow((int) Z_LVAL_P(fd), (int) Z_LVAL_P(action));
}

zend_long uart_get_modem_bits(zval *fd)
{
    int bits = 0;
    int result = ioctl((int) Z_LVAL_P(fd), TIOCMGET, &bits);

    return result < 0 ? -1 : (zend_long) bits;
}

zend_long uart_set_modem_bits(zval *fd, zval *bits)
{
    int b = (int) Z_LVAL_P(bits);

    return (zend_long) ioctl((int) Z_LVAL_P(fd), TIOCMSET, &b);
}

zend_long uart_set_bits(zval *fd, zval *bits)
{
    int b = (int) Z_LVAL_P(bits);

    return (zend_long) ioctl((int) Z_LVAL_P(fd), TIOCMBIS, &b);
}

zend_long uart_clear_bits(zval *fd, zval *bits)
{
    int b = (int) Z_LVAL_P(bits);

    return (zend_long) ioctl((int) Z_LVAL_P(fd), TIOCMBIC, &b);
}
