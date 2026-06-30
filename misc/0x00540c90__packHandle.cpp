// FUNC_NAME: packHandle
uint packHandle(uint value) {
    // Shifts right by 2 (divides by 4) and sets bit 30 (0x40000000)
    // This appears to pack a value into a 30-bit field with a high flag bit
    return (value >> 2) | 0x40000000;
}