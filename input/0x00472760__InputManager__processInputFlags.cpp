// FUNC_NAME: InputManager::processInputFlags
int __thiscall InputManager::processInputFlags(void* this_, int unused, unsigned int flags, void* outputData) {
    char flagResult;

    // Check if bit 2 (0x04) of flags is set by shifting right 2 and masking with 0xFFFFFF01
    // This likely tests a specific input flag
    flagResult = checkFlag((flags >> 2) & 0xFFFFFF01);
    if (flagResult != '\0') {
        // If flag active, check a byte at pointer +0x110, offset 0x62 (98 bytes)
        checkFlag(*(char*)(*(int*)((char*)this_ + 0x110) + 0x62));
    }

    // Check if bit 3 (0x08) of flags is set
    flagResult = checkFlag((flags >> 3) & 0xFFFFFF01);
    if (flagResult != '\0') {
        // If flag active, check a byte at pointer +0x110, offset 99 (0x63)
        checkFlag(*(char*)(*(int*)((char*)this_ + 0x110) + 99));
    }

    // Check if bit 1 (0x02) of flags is set
    flagResult = checkFlag((flags >> 1) & 0xFFFFFF01);
    if (flagResult != '\0') {
        // Copy 16 dwords (likely a 4x4 matrix) from offset 0x78 to local array
        unsigned int local[16]; // Actually 16 dwords, local_48[17] but only first 16 used
        unsigned int* src = (unsigned int*)((char*)this_ + 0x78);
        unsigned int* dst = local;
        for (int i = 0x10; i != 0; i = i - 1) {
            *dst = *src;
            src++;
            dst++;
        }
        // Apply matrix to output data (e.g., transform)
        applyMatrix(outputData, local);
        // Set a global constant (identity or default) and trigger a function with 0x20
        unsigned int localConst = globalMatrixConst;
        setGlobalFlag(0x20, &localConst);
    }
    return 0;
}