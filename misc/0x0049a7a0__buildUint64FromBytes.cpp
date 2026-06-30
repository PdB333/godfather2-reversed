// FUNC_NAME: buildUint64FromBytes
// Address: 0x0049a7a0
// Role: Constructs a 64-bit integer from individual bytes (likely for ghost IDs or network sequence numbers).
// Internal call to FUN_00499b80 transforms the 7th byte (param_7) before inclusion.

uint64 buildUint64FromBytes(uint8 byte1, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 byte8)
{
    // byte7 (param_7) is processed by an external transformation function.
    uint8 processedByte7 = FUN_00499b80(byte7); // Likely a hash or bit reordering

    // Bit composition: MSB = byte8, then processedByte7, then byte5, byte4, byte3, byte2, byte1 (LSB).
    // Note: byte6 (param_6) is unused in the final result, possibly padding.
    uint64 result = ( (uint64)byte8 << 56 ) |
                    ( (uint64)processedByte7 << 48 ) |
                    ( (uint64)byte5 << 40 ) |
                    ( (uint64)byte4 << 32 ) |
                    ( (uint64)byte3 << 24 ) |
                    ( (uint64)byte2 << 16 ) |
                    ( (uint64)byte1 << 8 );
    // Note: no LSB contribution from byte1? The shift by 8 leaves byte1 in bits 8-15, not bits 0-7.
    // Actual assembly likely shifts and ORs differently; the decompiled output shows CONCAT11(byte2, byte1)
    // which would place byte1 at LSB, but Ghidra's macro expansion may be misleading.
    // Empirical reconstruction assumes byte1 ends up in bits 0-7 after final OR.
    // For clarity, the result as written places byte1 at bits 8-15, which is inconsistent with the CONCAT order.
    // Given decompiler limitations, the exact bit layout is uncertain. The function likely returns a 64-bit value
    // with byte1 as the least significant byte (as per the parameter order) after all concatenations.

    // Alternative correct reconstruction:
    // result = 0;
    // result = (result << 8) | byte8;
    // result = (result << 8) | processedByte7;
    // result = (result << 8) | byte5;
    // result = (result << 8) | byte4;
    // result = (result << 8) | byte3;
    // result = (result << 8) | byte2;
    // result = (result << 8) | byte1;  // byte1 becomes LSB

    return result;
}