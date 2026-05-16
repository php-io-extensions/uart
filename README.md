# UART

[![PHP][badge-php]][php]
[![Zephir][badge-zephir]][zephir-install]
[![Platform][badge-platform]][linux]

PHP-controllable UART extension built with Zephir.

The UART extension gives PHP direct control over serial ports on Linux and macOS — configuring baud rate, framing, parity, flow control, and modem control lines, then performing raw reads and writes. Useful for microcontrollers, GPS modules, RS-232/RS-485 adapters, and any other device connected over a serial UART.

```shell
git clone https://github.com/DeptOfScrapyardRobotics/UART
cd UART
# Raspberry Pi / Debian Trixie:
bash install-debian-trixie.sh
# NVIDIA JetPack 6 (Jetson):
bash install-jetpack6.sh
# macOS:
bash install-macos.sh
```

## Requirements

- PHP 8.3+ with development headers (`php-dev` / `php-devel`)
- [Zephir][zephir-install] 0.19+
- [FD extension][fd-repo] — provides raw integer file descriptors via `Fd\FD::open()`
- Linux or macOS with a UART device (e.g. `/dev/ttyS0`, `/dev/ttyUSB0`, `/dev/ttyAMA0`, `/dev/tty.usbserial-*`)

> **macOS note:** Standard baud rates up to 230400 are available on all platforms. Linux-specific high rates (460800, 921600, and above) are only available on Linux.

## Installation

Install Zephir if you haven't already:

```shell
composer global require phalcon/zephir
```

Install the [FD extension][fd-repo] first — UART requires raw integer file descriptors that PHP's stream layer cannot provide:

```shell
git clone https://github.com/DeptOfScrapyardRobotics/FD
cd FD && bash install.sh
```

Then clone and build this extension:

```shell
git clone https://github.com/DeptOfScrapyardRobotics/UART
cd UART
# Raspberry Pi / Debian Trixie:
bash install-debian-trixie.sh
# NVIDIA JetPack 6 (Jetson):
bash install-jetpack6.sh
# macOS:
bash install-macos.sh
```

The install script handles the full workflow: clean → build → copy `.so` → write `30-uart.ini` into all detected `conf.d` directories → verify `php -m` → reload php-fpm if present.

To use a specific Zephir binary:

```shell
ZEPHIR_BIN=/path/to/zephir bash install-debian-trixie.sh
```

## API

All methods are static. File descriptors are plain integers. Use the [FD extension][fd-repo] to open and close them — PHP's stream-based `fopen` does not produce the raw integer FDs that termios requires.

```php
use Fd\FD;
use Uart\UARTConfig;
use Uart\UARTUse;

$fd = FD::open('/dev/ttyUSB0', 2); // O_RDWR = 2
// configure, then read/write ...
FD::close($fd);
```

---

### `Uart\UARTConfig`

Terminal attribute configuration on a UART file descriptor. All setters call `tcsetattr(TCSANOW)` internally — changes take effect immediately.

---

#### `setRaw(int $fd): int`

Puts the terminal into raw mode: no input processing, no echo, no signal generation. Equivalent to `cfmakeraw()` followed by `VMIN=1, VTIME=0`. This is the correct starting point for binary protocols. Returns `0` on success, `-1` on failure.

---

#### `setBaudRate(int $fd, int $baud): int`

Sets both input and output baud rate. Supported values on all platforms: `50`, `75`, `110`, `134`, `150`, `200`, `300`, `600`, `1200`, `1800`, `2400`, `4800`, `9600`, `19200`, `38400`, `57600`, `115200`, `230400`. Linux-only: `460800`, `500000`, `576000`, `921600`, `1000000`, `1152000`, `1500000`, `2000000`, `2500000`, `3000000`, `3500000`, `4000000`. Returns `0` on success, `-1` on unrecognised rate or failure.

---

#### `setDataBits(int $fd, int $bits): int`

Sets data bits per character: `5`, `6`, `7`, or `8`. Returns `0` on success, `-1` on invalid value or failure.

---

#### `setStopBits(int $fd, int $bits): int`

Sets stop bits: `1` or `2`. Returns `0` on success, `-1` on invalid value or failure.

---

#### `setParity(int $fd, int $parity): int`

Sets parity mode:

| Value | Mode |
|-------|------|
| `0` | None |
| `1` | Even |
| `2` | Odd |

Returns `0` on success, `-1` on invalid value or failure.

---

#### `setFlowControl(int $fd, int $flow): int`

Sets flow control mode:

| Value | Mode |
|-------|------|
| `0` | None |
| `1` | Hardware (RTS/CTS via `CRTSCTS`) |
| `2` | Software (XON/XOFF via `IXON`/`IXOFF`) |

Returns `0` on success, `-1` on invalid value or failure.

---

#### `getAttributes(int $fd): array`

Reads the full `termios` struct and returns it as an associative array. Returns `[]` on failure.

| Key | Type | Description |
|-----|------|-------------|
| `iflag` | `int` | Input mode flags (`c_iflag`) |
| `oflag` | `int` | Output mode flags (`c_oflag`) |
| `cflag` | `int` | Control mode flags (`c_cflag`) |
| `lflag` | `int` | Local mode flags (`c_lflag`) |
| `ispeed` | `int` | Input baud rate constant |
| `ospeed` | `int` | Output baud rate constant |
| `cc` | `array` | Control characters array, indexed `0`–`NCCS-1` |

---

#### `setAttributes(int $fd, array $attrs): int`

Applies terminal attributes from an associative array via `tcsetattr(TCSANOW)`. Accepts the same keys returned by `getAttributes()`. Partial updates are supported — only keys present in `$attrs` are applied. Returns `0` on success, `-1` on failure.

---

### `Uart\UARTUse`

Data transfer and line control on a UART file descriptor.

---

#### `read(int $fd, int $bytes_to_read): string`

Reads up to `$bytes_to_read` bytes from the device. Blocks until at least one byte is available (when in raw mode with `VMIN=1`). Returns the bytes as a binary string, or `""` on error.

---

#### `write(int $fd, string $data, int $bytes_to_write): int`

Writes `$bytes_to_write` bytes to the device. Returns the number of bytes written, or `-1` on failure.

---

#### `drain(int $fd): int`

Blocks until all data written to `$fd` has been physically transmitted. Returns `0` on success, `-1` on failure.

---

#### `flush(int $fd, int $queue_selector): int`

Discards queued data that has not yet been read or transmitted.

| Value | `queue_selector` constant | Effect |
|-------|--------------------------|--------|
| `0` | `TCIFLUSH` | Discard received but unread data |
| `1` | `TCOFLUSH` | Discard written but untransmitted data |
| `2` | `TCIOFLUSH` | Discard both |

Returns `0` on success, `-1` on failure.

---

#### `flow(int $fd, int $action): int`

Suspends or resumes data flow.

| Value | `action` constant | Effect |
|-------|-------------------|--------|
| `0` | `TCOOFF` | Suspend output |
| `1` | `TCOON` | Resume output |
| `2` | `TCIOFF` | Send STOP character, suspend input |
| `3` | `TCION` | Send START character, resume input |

Returns `0` on success, `-1` on failure.

---

#### `getModemBits(int $fd): int`

Returns the current modem control line status bitmask via `TIOCMGET`, or `-1` on failure. Compare against `TIOCM_*` values:

| Constant | Value | Line |
|----------|-------|------|
| `TIOCM_LE` | `0x001` | Line Enable |
| `TIOCM_DTR` | `0x002` | Data Terminal Ready |
| `TIOCM_RTS` | `0x004` | Request To Send |
| `TIOCM_CTS` | `0x020` | Clear To Send |
| `TIOCM_CAR` | `0x040` | Carrier Detect |
| `TIOCM_RNG` | `0x080` | Ring Indicator |
| `TIOCM_DSR` | `0x100` | Data Set Ready |

---

#### `setModemBits(int $fd, int $bits): int`

Replaces the full modem control line state via `TIOCMSET`. Returns `0` on success, `-1` on failure.

---

#### `setBits(int $fd, int $bits): int`

Asserts (raises) specific modem control lines without affecting others, via `TIOCMBIS`. Returns `0` on success, `-1` on failure.

---

#### `clearBits(int $fd, int $bits): int`

Deasserts (lowers) specific modem control lines without affecting others, via `TIOCMBIC`. Returns `0` on success, `-1` on failure.

---

## Usage

```php
use Fd\FD;
use Uart\UARTConfig;
use Uart\UARTUse;
```

---

### Basic send/receive at 115200 8N1

```php
$fd = FD::open('/dev/ttyUSB0', 2); // O_RDWR

UARTConfig::setRaw($fd);
UARTConfig::setBaudRate($fd, 115200);
UARTConfig::setDataBits($fd, 8);
UARTConfig::setStopBits($fd, 1);
UARTConfig::setParity($fd, 0);       // none
UARTConfig::setFlowControl($fd, 0);  // none

UARTUse::write($fd, "AT\r\n", 4);
UARTUse::drain($fd);

$response = UARTUse::read($fd, 64);

FD::close($fd);
```

---

### Hardware flow control (RTS/CTS)

```php
$fd = FD::open('/dev/ttyS0', 2);

UARTConfig::setRaw($fd);
UARTConfig::setBaudRate($fd, 115200);
UARTConfig::setFlowControl($fd, 1); // hardware

UARTUse::write($fd, $payload, strlen($payload));
UARTUse::drain($fd);

FD::close($fd);
```

---

### Flush and inspect attributes

```php
$fd = FD::open('/dev/ttyUSB0', 2);

UARTConfig::setRaw($fd);
UARTConfig::setBaudRate($fd, 9600);

UARTUse::flush($fd, 2); // TCIOFLUSH — clear both queues before use

$attrs = UARTConfig::getAttributes($fd);
printf("cflag=0x%08x  ispeed=%d  ospeed=%d\n",
    $attrs['cflag'], $attrs['ispeed'], $attrs['ospeed']);

FD::close($fd);
```

---

### Assert DTR, check CTS

```php
$fd = FD::open('/dev/ttyS0', 2);

UARTUse::setBits($fd, 0x002);    // TIOCM_DTR — raise DTR
$bits = UARTUse::getModemBits($fd);
$cts = ($bits & 0x020) !== 0;    // TIOCM_CTS
echo $cts ? "CTS asserted\n" : "CTS not asserted\n";

UARTUse::clearBits($fd, 0x002);  // lower DTR
FD::close($fd);
```

---

## License

Copyright © Project Saturn Studios, LLC. All rights reserved.

[badge-php]: https://img.shields.io/badge/php-%3E%3D8.3-blue
[badge-zephir]: https://img.shields.io/badge/zephir-0.19%2B-orange
[badge-platform]: https://img.shields.io/badge/platform-linux%20%7C%20macOS-lightgrey
[php]: https://www.php.net
[zephir-install]: https://docs.zephir-lang.com/latest/en/installation
[linux]: https://www.kernel.org
[fd-repo]: https://github.com/DeptOfScrapyardRobotics/FD
