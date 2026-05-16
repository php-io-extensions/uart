#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "uart-config.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

/*
 * CRTSCTS enables hardware RTS/CTS flow control. On Linux it is always defined.
 * On macOS it is defined only when _DARWIN_C_SOURCE is active (which PHP's build
 * system may suppress). Fall back to the BSD equivalents if needed.
 */
#ifndef CRTSCTS
#  ifdef CRTS_IFLOW
#    define CRTSCTS (CRTS_IFLOW | CCTS_OFLOW)
#  else
#    define CRTSCTS 0
#  endif
#endif

/*
 * Linux BOTHER / termios2 support for non-standard baud rates.
 *
 * We define the handful of symbols we need inline rather than including
 * <asm/termios.h>, which redefines struct termios and causes a hard
 * compilation error when <termios.h> is already included.
 *
 * struct termios2 layout and the TCGETS2/TCSETS2 ioctl numbers are stable
 * across all Linux architectures with 32-bit tcflag_t (x86, x86_64, ARM,
 * ARM64, RISC-V, etc.).  BOTHER and CBAUD are identical on all of them.
 */
#ifdef __linux__
struct termios2 {
    unsigned int  c_iflag;
    unsigned int  c_oflag;
    unsigned int  c_cflag;
    unsigned int  c_lflag;
    unsigned char c_line;
    unsigned char c_cc[19];
    unsigned int  c_ispeed;
    unsigned int  c_ospeed;
};
#ifndef BOTHER
#  define BOTHER   0x00001000
#endif
#ifndef CBAUD
#  define CBAUD    0x0000100F
#endif
#ifndef TCGETS2
#  define TCGETS2  0x802C542A
#endif
#ifndef TCSETS2
#  define TCSETS2  0x402C542B
#endif
#endif /* __linux__ */

zend_long uart_set_raw(zval *fd)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    cfmakeraw(&tty);
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 0;

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

zend_long uart_set_baud_rate(zval *fd, zval *baud)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);
    speed_t speed;

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    switch (Z_LVAL_P(baud)) {
        case 50:      speed = B50;      break;
        case 75:      speed = B75;      break;
        case 110:     speed = B110;     break;
        case 134:     speed = B134;     break;
        case 150:     speed = B150;     break;
        case 200:     speed = B200;     break;
        case 300:     speed = B300;     break;
        case 600:     speed = B600;     break;
        case 1200:    speed = B1200;    break;
        case 1800:    speed = B1800;    break;
        case 2400:    speed = B2400;    break;
        case 4800:    speed = B4800;    break;
        case 9600:    speed = B9600;    break;
        case 19200:   speed = B19200;   break;
        case 38400:   speed = B38400;   break;
        case 57600:   speed = B57600;   break;
        case 115200:  speed = B115200;  break;
        case 230400:  speed = B230400;  break;
#ifdef B460800
        case 460800:  speed = B460800;  break;
#endif
#ifdef B500000
        case 500000:  speed = B500000;  break;
#endif
#ifdef B576000
        case 576000:  speed = B576000;  break;
#endif
#ifdef B921600
        case 921600:  speed = B921600;  break;
#endif
#ifdef B1000000
        case 1000000: speed = B1000000; break;
#endif
#ifdef B1152000
        case 1152000: speed = B1152000; break;
#endif
#ifdef B1500000
        case 1500000: speed = B1500000; break;
#endif
#ifdef B2000000
        case 2000000: speed = B2000000; break;
#endif
#ifdef B2500000
        case 2500000: speed = B2500000; break;
#endif
#ifdef B3000000
        case 3000000: speed = B3000000; break;
#endif
#ifdef B3500000
        case 3500000: speed = B3500000; break;
#endif
#ifdef B4000000
        case 4000000: speed = B4000000; break;
#endif
        default:
#ifdef __linux__
            /*
             * Rate has no standard Bxxxxx constant — try the Linux
             * BOTHER / termios2 path which accepts any numeric rate
             * the hardware supports.
             */
            {
                struct termios2 tio2;
                if (ioctl(_fd, TCGETS2, &tio2) == 0) {
                    tio2.c_cflag &= ~CBAUD;
                    tio2.c_cflag |=  BOTHER;
                    tio2.c_ispeed = (speed_t) Z_LVAL_P(baud);
                    tio2.c_ospeed = (speed_t) Z_LVAL_P(baud);
                    return (zend_long) ioctl(_fd, TCSETS2, &tio2);
                }
            }
#endif
            return -1;
    }

    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

zend_long uart_set_data_bits(zval *fd, zval *bits)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    tty.c_cflag &= ~CSIZE;

    switch (Z_LVAL_P(bits)) {
        case 5: tty.c_cflag |= CS5; break;
        case 6: tty.c_cflag |= CS6; break;
        case 7: tty.c_cflag |= CS7; break;
        case 8: tty.c_cflag |= CS8; break;
        default: return -1;
    }

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

zend_long uart_set_stop_bits(zval *fd, zval *bits)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    switch (Z_LVAL_P(bits)) {
        case 1: tty.c_cflag &= ~CSTOPB; break;
        case 2: tty.c_cflag |=  CSTOPB; break;
        default: return -1;
    }

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

/* parity: 0 = none, 1 = even, 2 = odd */
zend_long uart_set_parity(zval *fd, zval *parity)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    switch (Z_LVAL_P(parity)) {
        case 0:
            tty.c_cflag &= ~PARENB;
            tty.c_iflag &= ~INPCK;
            break;
        case 1:
            tty.c_cflag |=  PARENB;
            tty.c_cflag &= ~PARODD;
            tty.c_iflag |=  INPCK;
            break;
        case 2:
            tty.c_cflag |= PARENB;
            tty.c_cflag |= PARODD;
            tty.c_iflag |= INPCK;
            break;
        default: return -1;
    }

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

/* flow: 0 = none, 1 = hardware (RTS/CTS), 2 = software (XON/XOFF) */
zend_long uart_set_flow_control(zval *fd, zval *flow)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    switch (Z_LVAL_P(flow)) {
        case 0:
            tty.c_cflag &= ~CRTSCTS;
            tty.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case 1:
            tty.c_cflag |=  CRTSCTS;
            tty.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case 2:
            tty.c_cflag &= ~CRTSCTS;
            tty.c_iflag |=  (IXON | IXOFF);
            tty.c_iflag &= ~IXANY;
            break;
        default: return -1;
    }

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}

void uart_get_attributes(zval *return_value, zval *fd)
{
    struct termios tty;

    array_init(return_value);

    if (tcgetattr((int) Z_LVAL_P(fd), &tty) < 0) {
        return;
    }

    add_assoc_long(return_value, "iflag",  (zend_long) tty.c_iflag);
    add_assoc_long(return_value, "oflag",  (zend_long) tty.c_oflag);
    add_assoc_long(return_value, "cflag",  (zend_long) tty.c_cflag);
    add_assoc_long(return_value, "lflag",  (zend_long) tty.c_lflag);
    add_assoc_long(return_value, "ispeed", (zend_long) cfgetispeed(&tty));
    add_assoc_long(return_value, "ospeed", (zend_long) cfgetospeed(&tty));

    zval cc_array;
    array_init(&cc_array);
    for (int i = 0; i < NCCS; i++) {
        add_index_long(&cc_array, i, (zend_long) tty.c_cc[i]);
    }
    add_assoc_zval(return_value, "cc", &cc_array);
}

zend_long uart_set_attributes(zval *fd, zval *attrs)
{
    struct termios tty;
    int _fd = (int) Z_LVAL_P(fd);
    zval *v;

    if (tcgetattr(_fd, &tty) < 0) {
        return -1;
    }

    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "iflag", sizeof("iflag") - 1)) != NULL) {
        tty.c_iflag = (tcflag_t) zval_get_long(v);
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "oflag", sizeof("oflag") - 1)) != NULL) {
        tty.c_oflag = (tcflag_t) zval_get_long(v);
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "cflag", sizeof("cflag") - 1)) != NULL) {
        tty.c_cflag = (tcflag_t) zval_get_long(v);
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "lflag", sizeof("lflag") - 1)) != NULL) {
        tty.c_lflag = (tcflag_t) zval_get_long(v);
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "ispeed", sizeof("ispeed") - 1)) != NULL) {
        cfsetispeed(&tty, (speed_t) zval_get_long(v));
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "ospeed", sizeof("ospeed") - 1)) != NULL) {
        cfsetospeed(&tty, (speed_t) zval_get_long(v));
    }
    if ((v = zend_hash_str_find(Z_ARRVAL_P(attrs), "cc", sizeof("cc") - 1)) != NULL
            && Z_TYPE_P(v) == IS_ARRAY) {
        zval *cc_v;
        for (int i = 0; i < NCCS; i++) {
            cc_v = zend_hash_index_find(Z_ARRVAL_P(v), i);
            if (cc_v != NULL) {
                tty.c_cc[i] = (cc_t) zval_get_long(cc_v);
            }
        }
    }

    return (zend_long) tcsetattr(_fd, TCSANOW, &tty);
}
