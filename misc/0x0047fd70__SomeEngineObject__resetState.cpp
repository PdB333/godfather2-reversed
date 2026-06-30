// FUNC_NAME: SomeEngineObject::resetState
int SomeEngineObject::resetState() {
    // Reset global data structures (likely singleton managers)
    clearGlobalData(&g_globalData1);   // DAT_0120e970
    clearGlobalData(&g_globalData2);   // DAT_0120e960

    // Temporary buffer for color/vector operation (9 bytes: dword, dword, byte)
    struct {
        uint32_t field0;
        uint32_t field4;
        uint8_t  field8;
    } temp;

    // Use current color value at this+0x58 (packed RGBA or similar)
    temp.field0 = *(uint32_t*)((uint8_t*)this + 0x58); // +0x58
    temp.field4 = 0;
    temp.field8 = 0;
    setColorBuffer(&temp, 0); // Second param unknown (0)

    // Overwrite with default color from global
    temp.field0 = g_defaultColor; // DAT_0120eb00
    temp.field4 = 0;
    temp.field8 = 0;
    setColorBuffer(&temp, 0);

    // Clear flag byte at this+0x90 (e.g., "needsUpdate" or "dirty")
    *(uint8_t*)((uint8_t*)this + 0x90) = 0;

    return 1;
}