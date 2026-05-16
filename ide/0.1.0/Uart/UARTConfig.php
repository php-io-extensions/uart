<?php

namespace Uart;

class UARTConfig
{


    /**
     * Configure the terminal for raw I/O (no processing, no echo, no signals).
     * Calls cfmakeraw() then sets VMIN=1, VTIME=0: block until at least one byte arrives.
     * This is the correct starting point before setting baud rate and framing.
     *
     * @param int $fd File descriptor opened with Fd\FD::open()
     * @return int 0 on success, -1 on failure
     */
    public static function setRaw(int $fd): int
    {
    }

    /**
     * Set baud rate (input and output simultaneously).
     * Supported on all platforms: 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800,
     * 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400.
     * Linux-only: 460800, 500000, 576000, 921600, 1000000, 1152000, 1500000,
     * 2000000, 2500000, 3000000, 3500000, 4000000.
     *
     * @param int $fd File descriptor
     * @param int $baud Numeric baud rate (e.g. 9600, 115200)
     * @return int 0 on success, -1 on unrecognised rate or failure
     */
    public static function setBaudRate(int $fd, int $baud): int
    {
    }

    /**
     * Set number of data bits per character (5, 6, 7, or 8).
     *
     * @param int $fd File descriptor
     * @param int $bits 5, 6, 7, or 8
     * @return int 0 on success, -1 on invalid value or failure
     */
    public static function setDataBits(int $fd, int $bits): int
    {
    }

    /**
     * Set number of stop bits (1 or 2).
     *
     * @param int $fd File descriptor
     * @param int $bits 1 or 2
     * @return int 0 on success, -1 on invalid value or failure
     */
    public static function setStopBits(int $fd, int $bits): int
    {
    }

    /**
     * Set parity mode: 0 = none, 1 = even, 2 = odd.
     *
     * @param int $fd File descriptor
     * @param int $parity 0 (none), 1 (even), or 2 (odd)
     * @return int 0 on success, -1 on invalid value or failure
     */
    public static function setParity(int $fd, int $parity): int
    {
    }

    /**
     * Set flow control mode: 0 = none, 1 = hardware (RTS/CTS), 2 = software (XON/XOFF).
     *
     * @param int $fd File descriptor
     * @param int $flow 0 (none), 1 (hardware), or 2 (software)
     * @return int 0 on success, -1 on invalid value or failure
     */
    public static function setFlowControl(int $fd, int $flow): int
    {
    }

    /**
     * Read all current terminal attributes into an associative array.
     * Keys: iflag, oflag, cflag, lflag, ispeed, ospeed, cc (array indexed 0..NCCS-1).
     * Returns empty array on failure.
     *
     * @param int $fd File descriptor
     * @return array
     */
    public static function getAttributes(int $fd): array
    {
    }

    /**
     * Apply terminal attributes from an associative array via tcsetattr(TCSANOW).
     * Accepts the same keys returned by getAttributes(). Partial updates are supported —
     * only keys present in $attrs are applied; the rest are read from the current state.
     *
     * @param int $fd File descriptor
     * @param array $attrs Attribute array
     * @return int 0 on success, -1 on failure
     */
    public static function setAttributes(int $fd, $attrs): int
    {
    }
}
