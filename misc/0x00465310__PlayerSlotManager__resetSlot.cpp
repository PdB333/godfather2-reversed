// FUNC_NAME: PlayerSlotManager::resetSlot
// Clears all state fields for a given slot identified by index in EAX (lower byte).
// Each slot is 0x168 bytes, with data starting at offset 0x10 from slot base.
void __fastcall PlayerSlotManager::resetSlot(PlayerSlotManager* this, int slotIndex)
{
    // slotIndex comes from the lower byte of EAX (masked to 0xFF)
    int actualSlotIndex = slotIndex & 0xFF;
    
    // Compute pointer to the slot's data region (each slot is 0x168 bytes, data starts at +0x10)
    char* slotData = reinterpret_cast<char*>(this) + actualSlotIndex * 0x168 + 0x10;
    
    // Clear byte fields at offsets 0x37 and 0x4f (likely flags or state)
    slotData[0x37] = 0;
    slotData[0x4f] = 0;
    
    // Clear dword at offset 0x158 (likely a counter or pointer)
    *reinterpret_cast<uint32_t*>(slotData + 0x158) = 0;
    
    // Clear an array of 16 structures (each 12 bytes) starting at offset 0x58
    // Each struct appears to be three consecutive dwords (offsets -8, -4, 0 relative to .60)
    // We clear 16 entries of 12 bytes each = 192 bytes from 0x58 to 0x118-1
    uint32_t* p = reinterpret_cast<uint32_t*>(slotData + 0x60);
    int count = 0x10;
    do {
        *(p - 2) = 0; // offset 0x58
        *(p - 1) = 0; // offset 0x5C
        *p = 0;       // offset 0x60
        p += 4;       // advance 16 bytes (4 dwords) – but we only wrote 3 dwords? Actually p += 4 moves pointer by 4*4=16 bytes, but we only wrote 3 dwords per iteration.
        // The decompiled shows puVar1 = puVar1 + 4 which is 4 ints = 16 bytes, but we only wrote 3 dwords per iteration.
        // This might be an inefficiency or there's an extra field at +12 that wasn't cleared.
        // However, we replicate the exact logic: clear 3 dwords, then advance by 4 dwords (16 bytes).
        count--;
    } while (count != 0);
}