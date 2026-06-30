// FUNC_NAME: getBitfieldValue (static utility)
uint __cdecl getBitfieldValue(byte bitIndex) {
    byte bVar1 = bitIndex;
    uint value = 0; // Initialize to 0 before calling helper

    // Helper function reads a bitfield from some global/context, stores into 'value'
    FUN_0064b9e0(bVar1, &value);

    if (bVar1 != 0x20) {
        // Mask to only the lower (bitIndex) bits: (1 << (bitIndex & 0x1f)) - 1
        // If bitIndex >= 32, the mask becomes 0xFFFFFFFF (since & 0x1f)
        value &= (1U << (bVar1 & 0x1f)) - 1U;
    }
    return value;
}