// FUNC_NAME: setThreadLocalStorageSlot
void setThreadLocalStorageSlot(uint32_t value) {
    // Windows TLS: fs:[0x2c] -> pointer to TLS array
    uint32_t* tlsBase = (uint32_t*)__readfsdword(0x2c);
    // Check a flag at offset 0x34 in TLS data
    int slotIndex = (*(int*)((uint8_t*)tlsBase + 0x34) != 0) ? 1 : 0;
    // Global array at 0x011f6be8 (likely extern declaration elsewhere)
    ((uint32_t*)0x011f6be8)[slotIndex] = value;
}