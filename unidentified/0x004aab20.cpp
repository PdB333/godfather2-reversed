// FUN_004aab20: TimeManager::getTimestamp
// Function address: 0x004aab20
// Role: Returns a composite timestamp from a global time base (via TLS) and an instance-specific offset

int __fastcall TimeManager::getTimestamp() {
    // Fetch TLS pointer from FS segment (offset 0x2C)
    int** tlsSlots = (int**)__readfsdword(0x2C);
    // First TLS slot holds a pointer to the global game state structure
    int* globalState = *tlsSlots;
    // Base timestamp is at offset +0x08 from globalState
    int baseTime = globalState[2]; // sizeof(int) = 4, so index 2 = byte offset 0x08
    // Per-instance adjustment stored at this+0x18
    int localAdjust = *(int*)((uint8_t*)this + 0x18);
    // Constant bias 0x40 (likely frame/tick alignment)
    return baseTime + 0x40 + localAdjust;
}