// FUNC_NAME: isSpecialTypeWithHighBit
uint32_t isSpecialTypeWithHighBit(uint32_t type) // type passed in EAX
{
    uint32_t lowBits = type & 0x7FFF;
    if ((type & 0x8000) != 0 && (lowBits == 0xD || lowBits == 0x12)) {
        return 1;
    }
    return 0;
}