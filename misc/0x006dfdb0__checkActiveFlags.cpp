// FUNC_NAME: checkActiveFlags
bool __fastcall checkActiveFlags(int this) {
    // Check if bit 0x17 (23) at offset 0x249c is set, or if bit 0x9 at offset 0x8e0 is set
    // If either flag is active, return true, otherwise false
    if (((*(uint*)(this + 0x249c) >> 0x17) & 1) == 0 &&
        ((*(uint*)(this + 0x8e0) >> 9) & 1) == 0) {
        return false;
    }
    return true;
}