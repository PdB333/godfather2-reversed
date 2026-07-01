// FUNC_NAME: BNKStreamManager::setStreamActive

void __thiscall BNKStreamManager::setStreamActive(bool enable) {
    // Offset 0x118: flags (bitmask)
    uint32_t& flags = *(uint32_t*)((uint8_t*)this + 0x118);

    if (enable) {
        // Copy stream data if source buffer is present
        if (g_streamSourceData != 0) {
            // Offset 0x3c: stream buffer (0x8000 bytes)
            // FUN_00408900 is memcpy-like copy function
            memcpy((void*)((uint8_t*)this + 0x3c), &g_streamSourceData, 0x8000);
        }
        // Set bit 11 (0x800) and clear bits 12-14 (0x7000)
        flags = (flags & 0xFFFF8FFF) | 0x800;
    } else {
        // Clear bit 11 and bits 12-14
        flags = flags & 0xFFFF87FF;
    }
}