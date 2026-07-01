// FUNC_NAME: clearLowByteAndProcessData
void clearLowByteAndProcessData(void)
{
    uint data[2]; // Two 32-bit values, likely packet header or sequence info

    // Clear the low byte of the first element (e.g., remove packet type flag)
    data[0] = data[0] & 0xffffff00;

    // Call processing function with pointer to the array, pointer to second element,
    // and the masked first value
    FUN_0088f510(data, &data[1], data[0]);
}