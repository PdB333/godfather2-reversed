// FUNC_NAME: setFullscreenWorkArea
void setFullscreenWorkArea(void) {
    // Build a 24-byte work area structure from global display settings.
    // The structure likely contains a modified RECT followed by two 8-byte fields (e.g., for multi-monitor or padding).
    // local_18 holds the modified left/top (as a 64-bit combined value), local_10 and local_8 hold additional data.
    ulonglong local_18;
    uint64_t local_10;
    uint64_t local_8;

    local_10 = *(uint64_t*)0x00e50b5c;
    local_8 = *(uint64_t*)0x00e50b64;

    // Check if the "work area locked" flag (bit 0 of the second dword at 0x00e50b54) is clear.
    // If not set, we are allowed to adjust the work area.
    if ((*(uint32_t*)(0x00e50b54 + 4) & 1) == 0) {
        // Build a 64-bit value from the left (low 32 bits) and top (high 32 bits) from the global structure.
        // Then clear bits 2 and 3 of the top field (bits 34 and 35 overall) – possibly "keep taskbar" or "allow covering".
        local_18 = CONCAT44(*(uint32_t*)(0x00e50b54 + 4), *(uint32_t*)0x00e50b54) & 0xfffffff3ffffffff;
        // Set the work area for the primary monitor. uiParam = 0x18 (24 bytes) is the size of the structure.
        SystemParametersInfoA(0x33, 0x18, &local_18, 0);
    }
    return;
}