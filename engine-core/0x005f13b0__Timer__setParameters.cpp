// FUNC_NAME: Timer::setParameters

void __fastcall Timer::setParameters(int thisPtr, uint8_t param_byte, uint32_t param_unknown, float param_float)
{
    // +0x1c: mode/flag byte
    *(uint8_t *)(thisPtr + 0x1c) = param_byte;
    // +0x1d: cleared byte
    *(uint8_t *)(thisPtr + 0x1d) = 0;
    // +0x10: flags (OR with 0x120 = bits 5 and 8)
    *(uint16_t *)(thisPtr + 0x10) |= 0x120;
    // Apply global time scale to input float and round to nearest integer
    float scaled = param_float * DAT_00e445e0;
    int rounded = (int)(scaled + 0.5f); // ROUND (nearest integer)
    // +0x14: scaled time value
    *(uint32_t *)(thisPtr + 0x14) = rounded;
    // +0x20: additional parameter
    *(uint32_t *)(thisPtr + 0x20) = param_unknown;
}