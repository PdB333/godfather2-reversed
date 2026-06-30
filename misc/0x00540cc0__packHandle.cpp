// FUNC_NAME: packHandle
// Encodes a 32-bit value (typically an aligned pointer or index) by shifting right 2 bits
// and setting bit 30 (0x40000000) as a flag. Used extensively for object handles.
uint packHandle(uint value)
{
    return (value >> 2) | 0x40000000;
}