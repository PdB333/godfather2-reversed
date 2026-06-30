// FUNC_NAME: packEventData
uint32_t __cdecl packEventData(float timeValue, int typeId)
{
    // Global scale factor to convert time into internal units (ticks)
    extern float s_timeScaleFactor; // DAT_00e2e230

    uint8_t flagByte;
    if (typeId == 1) {
        flagByte = 0x82; // Event type 1: flag bits 10000010
    } else if (typeId == 2) {
        flagByte = 0x42; // Event type 2: flag bits 01000010
    } else {
        flagByte = 0x02; // Default type: flag bits 00000010
    }

    // Scale the time and truncate to 16-bit signed integer
    int16_t scaledTicks = (int16_t)(timeValue * s_timeScaleFactor);

    // Lower 16 bits: [flagByte (8 bits) | 0x01 (8 bits)]
    uint16_t lowerBits = ((uint16_t)flagByte << 8) | 0x01;

    // Pack into 32-bit: high 16 = scaled ticks, low 16 = {flag, 0x01}
    return ( ((uint32_t)(uint16_t)scaledTicks) << 16 ) | lowerBits;
}