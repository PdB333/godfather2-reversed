// FUNC_NAME: HandleTable::isValidHandle
bool __fastcall HandleTable::isValidHandle(uint32_t handle)
{
    uint16_t index = handle & 0xFFFF;
    if (index >= 0x200) {
        return false;
    }

    // Base pointer to the handle table (each entry 0x30 bytes)
    uint8_t* tableBase = *(uint8_t**)0x012234bc; // DAT_012234bc
    if (tableBase == nullptr) {
        return false;
    }

    // Compute entry pointer: base + 0x10 + index * 0x30
    HandleEntry* entry = (HandleEntry*)(tableBase + 0x10 + index * 0x30);
    if (entry == nullptr) {
        return false;
    }

    // Validate stored handle matches
    if (entry->storedHandle != handle) {
        return false;
    }

    // Check some validity flag at offset 0x10
    if (entry->validFlag == 0) {
        return false;
    }

    return true;
}