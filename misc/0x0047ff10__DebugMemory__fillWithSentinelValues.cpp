// FUNC_NAME: DebugMemory::fillWithSentinelValues
void __thiscall DebugMemory::fillWithSentinelValues(void) {
    // Fill 0x200 bytes starting at 'this' with debug sentinel values
    // Pattern: each 16-byte block gets: 0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
    unsigned int *block = reinterpret_cast<unsigned int*>(reinterpret_cast<uintptr_t>(this) + 8);
    for (int i = 0x1f; i >= 0; --i) {
        block[-2] = 0xBADBADBA;  // +0x00 relative to this
        block[-1] = 0xBEEFBEEF;  // +0x04
        block[0]  = 0xEAC15A55;  // +0x08
        block[1]  = 0x91100911;  // +0x0C
        block += 4;              // advance 16 bytes
    }
    // Set the DWORD at offset 0x200 to 0 (likely a null pointer or flag)
    *reinterpret_cast<unsigned int*>(reinterpret_cast<uintptr_t>(this) + 0x200) = 0;
}