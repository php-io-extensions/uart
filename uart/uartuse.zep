namespace Uart;

class UARTUse
{
    /**
     * Read up to bytes_to_read bytes from the UART device.
     * Blocks until data is available (behaviour controlled by VMIN/VTIME set via UARTConfig).
     * @param int fd File descriptor
     * @param int bytes_to_read Maximum number of bytes to read
     * @return string Data read as a binary string, or "" on error
     */
    public static function read(int fd, int bytes_to_read) -> string
    {
        var result;

        let result = uart_read(fd, bytes_to_read);

        return result;
    }

    /**
     * Write data to the UART device.
     * @param int fd File descriptor
     * @param var data Data string to transmit
     * @param int bytes_to_write Number of bytes to write
     * @return int Bytes written on success, -1 on failure
     */
    public static function write(int fd, var data, int bytes_to_write) -> int
    {
        int result;
        string payload = data;

        let result = uart_write(fd, payload, bytes_to_write);

        return result;
    }

    /**
     * Block until all output written to fd has been physically transmitted.
     * @param int fd File descriptor
     * @return int 0 on success, -1 on failure
     */
    public static function drain(int fd) -> int
    {
        int result;

        let result = uart_drain(fd);

        return result;
    }

    /**
     * Discard queued data.
     * queue_selector: 0 = TCIFLUSH (input), 1 = TCOFLUSH (output), 2 = TCIOFLUSH (both).
     * @param int fd File descriptor
     * @param int queue_selector 0, 1, or 2
     * @return int 0 on success, -1 on failure
     */
    public static function flush(int fd, int queue_selector) -> int
    {
        int result;

        let result = uart_flush(fd, queue_selector);

        return result;
    }

    /**
     * Suspend or resume data flow.
     * action: 0 = TCOOFF (suspend output), 1 = TCOON (resume output),
     *         2 = TCIOFF (suspend input), 3 = TCION (resume input).
     * @param int fd File descriptor
     * @param int action 0, 1, 2, or 3
     * @return int 0 on success, -1 on failure
     */
    public static function flow(int fd, int action) -> int
    {
        int result;

        let result = uart_flow(fd, action);

        return result;
    }

    /**
     * Get modem control line status bitmask via TIOCMGET.
     * Compare against TIOCM_DTR (0x002), TIOCM_RTS (0x004), TIOCM_CTS (0x020), etc.
     * @param int fd File descriptor
     * @return int Modem status bitmask, or -1 on failure
     */
    public static function getModemBits(int fd) -> int
    {
        int result;

        let result = uart_get_modem_bits(fd);

        return result;
    }

    /**
     * Replace the full modem control line state via TIOCMSET.
     * @param int fd File descriptor
     * @param int bits Bitmask of TIOCM_* flags
     * @return int 0 on success, -1 on failure
     */
    public static function setModemBits(int fd, int bits) -> int
    {
        int result;

        let result = uart_set_modem_bits(fd, bits);

        return result;
    }

    /**
     * Assert (raise) specific modem control lines without affecting others, via TIOCMBIS.
     * @param int fd File descriptor
     * @param int bits Bitmask of TIOCM_* flags to raise
     * @return int 0 on success, -1 on failure
     */
    public static function setBits(int fd, int bits) -> int
    {
        int result;

        let result = uart_set_bits(fd, bits);

        return result;
    }

    /**
     * Deassert (lower) specific modem control lines without affecting others, via TIOCMBIC.
     * @param int fd File descriptor
     * @param int bits Bitmask of TIOCM_* flags to lower
     * @return int 0 on success, -1 on failure
     */
    public static function clearBits(int fd, int bits) -> int
    {
        int result;

        let result = uart_clear_bits(fd, bits);

        return result;
    }
}
