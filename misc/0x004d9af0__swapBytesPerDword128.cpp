// FUNC_NAME: swapBytesPerDword128
void __fastcall swapBytesPerDword128(uint8_t* buffer)
{
    // Reverses byte order within each 32-bit word of a 16-byte (128-bit) block.
    // This is used for endianness conversion of a 128-bit value composed of 4 DWORDs.
    uint8_t temp;

    // Word 0 (bytes 0-3)
    temp = buffer[0];
    buffer[0] = buffer[3];
    buffer[3] = temp;

    temp = buffer[1];
    buffer[1] = buffer[2];
    buffer[2] = temp;

    // Word 1 (bytes 4-7)
    temp = buffer[4];
    buffer[4] = buffer[7];
    buffer[7] = temp;

    temp = buffer[5];
    buffer[5] = buffer[6];
    buffer[6] = temp;

    // Word 2 (bytes 8-11)
    temp = buffer[8];
    buffer[8] = buffer[11];
    buffer[11] = temp;

    temp = buffer[9];
    buffer[9] = buffer[10];
    buffer[10] = temp;

    // Word 3 (bytes 12-15)
    temp = buffer[12];
    buffer[12] = buffer[15];
    buffer[15] = temp;

    temp = buffer[13];
    buffer[13] = buffer[14];
    buffer[14] = temp;
}