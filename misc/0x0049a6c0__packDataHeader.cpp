// FUNC_NAME: packDataHeader
// Address: 0x0049a6c0
// Role: Packs two byte values into a 64-bit identifier with a fixed prefix byte (0x03).
// The result is constructed as: top 8 bits zero, then 0x03, then param2 (zero-extended to 16 bits), then param3 as 32-bit.

#include <cstdint>

uint64_t packDataHeader(uint8_t param2, uint8_t param3) {
    // Build 64-bit value: 0x0003????00000000 | param3
    // where ???? is param2 zero-extended to 16 bits.
    return ((uint64_t)0x03 << 48) | ((uint64_t)param2 << 32) | (uint32_t)param3;
}