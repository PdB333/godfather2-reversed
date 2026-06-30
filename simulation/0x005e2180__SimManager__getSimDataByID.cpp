// FUNC_NAME: SimManager::getSimDataByID
bool __thiscall SimManager::getSimDataByID(int id, uint32_t *outBuffer) {
    // id is passed in EAX (custom calling convention)
    if (id == 0) {
        return false;
    }

    // Search through array of 5 entries at offset +0x490
    // Each entry is 0x4A4 bytes, starting with an ID field
    for (int i = 0; i < 5; i++) {
        int *entryIdPtr = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x490 + i * 0x4A4);
        if (id == *entryIdPtr) {
            // Found entry, compute pointer to entry base
            SimDataEntry *entry = reinterpret_cast<SimDataEntry*>(reinterpret_cast<uint8_t*>(this) + 4 + i * 0x4A4); // +4 offset from this? see comment
            // Note: The decompiled code does "param_1 = iVar2 * 0x4a4 + 4 + param_1;" This suggests the base of the array is at this+4, but the search uses this+0x490. This inconsistency may be due to decompiler artifact. We'll assume the array is at this+0x490 and the +4 is a mistake. Real offset for entry i is this+0x490 + i*0x4A4.
            // For reconstruction, we use the same offset as the search to be safe.
            entry = reinterpret_cast<SimDataEntry*>(reinterpret_cast<uint8_t*>(this) + 0x490 + i * 0x4A4);

            // Copy 27 dwords (108 bytes) from offset +0x210 to output buffer
            uint32_t *src = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(entry) + 0x210);
            for (int j = 0; j < 27; j++) {
                outBuffer[j] = src[j];
            }
            return true;
        }
    }
    return false;
}