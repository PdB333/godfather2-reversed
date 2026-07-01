// FUN_008a6ea0: TypedValueGetter::getValueIfTypeMatches (based on offset pattern)
// Checks if object at +0x8 has a specific type ID (stored at DAT_00e54408), and returns the value at +0xC if so, else 0.
// Offsets: +0x8 = typeId, +0xC = value
uint32_t getTypedValue(uint32_t* thisPtr) {
    // DAT_00e54408 is the expected type identifier
    if (*(uint32_t*)((uint32_t)thisPtr + 8) == (uint32_t)DAT_00e54408) {
        return *(uint32_t*)((uint32_t)thisPtr + 0xC);
    }
    return 0;
}