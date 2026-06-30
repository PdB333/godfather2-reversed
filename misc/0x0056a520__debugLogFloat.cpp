// FUNC_NAME: debugLogFloat
void debugLogFloat(float value) {
    char buffer[16]; // +0x0 buffer[15] + local_5 at offset 0x0F
    __snprintf(buffer, 0x10, "%f", (double)value);
    buffer[15] = 0; // local_5 = 0

    // Global debug manager object at address 0x012234e0
    // Call virtual method at vtable offset 0x14 (function index 5) with tags
    // 0x48445752 = 'HDRW', 0x48445350 = 'HDSP'
    (*(void (__thiscall *)(void*, uint32_t, uint32_t, const char*))(*(uint32_t*)0x012234e0 + 0x14))(
        *(void**)0x012234e0, 0x48445752, 0x48445350, buffer);
}