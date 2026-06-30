// FUNC_NAME: endianSwap16Bytes
void __fastcall endianSwap16Bytes(uint8_t* buffer)
{
    uint8_t temp;

    // Swap bytes within each 32-bit word to reverse endianness (little->big or big->little)
    // Word 0: indices 0-3
    temp = buffer[0];
    buffer[0] = buffer[3];
    buffer[3] = temp;

    temp = buffer[1];
    buffer[1] = buffer[2];
    buffer[2] = temp;

    // Word 1: indices 4-7
    temp = buffer[4];
    buffer[4] = buffer[7];
    buffer[7] = temp;

    temp = buffer[5];
    buffer[5] = buffer[6];
    buffer[6] = temp;

    // Word 2: indices 8-11
    temp = buffer[8];
    buffer[8] = buffer[11];
    buffer[11] = temp;

    temp = buffer[9];
    buffer[9] = buffer[10];
    buffer[10] = temp;

    // Word 3: indices 12-15
    temp = buffer[12];
    buffer[12] = buffer[15];
    buffer[15] = temp;

    temp = buffer[13];
    buffer[13] = buffer[14];
    buffer[14] = temp;
}