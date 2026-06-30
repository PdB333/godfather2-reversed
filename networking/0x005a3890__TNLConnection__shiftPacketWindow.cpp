// FUNC_NAME: TNLConnection::shiftPacketWindow
// Address: 0x005a3890
// Shifts packet entries within a sliding window buffer (32-byte entries).
// Removes entries from the source range (param_2 to param_3) by moving them to the destination range (param_1 based).

struct PacketEntry {
    uint8_t  unknown[0x1C]; // 0x00-0x1B
    uint32_t dwordAt1C;     // +0x1C likely sequence number or timestamp
};

// Destructor-like call for a PacketEntry (frees internal resources)
void __fastcall packetEntryDestructor(PacketEntry* entry);  // FUN_005a0a00

// Generic cleanup function (likely flushes some cache or updates state)
void __thiscall connectionCleanup(void);  // FUN_005a1060

// External memory deallocation function pointer
extern void (*g_freePtr)(void*);  // DAT_0119caf4

// Returns pointer to the first moved entry (or one before the original base)
PacketEntry* __thiscall TNLConnection::shiftPacketWindow(PacketEntry* dstBase, PacketEntry* srcStart, PacketEntry* srcEnd) {
    int32_t count = (reinterpret_cast<uint32_t>(srcEnd) - reinterpret_cast<uint32_t>(srcStart)) >> 5; // Number of 32-byte entries between srcStart and srcEnd
    PacketEntry* dst = reinterpret_cast<PacketEntry*>(reinterpret_cast<uint32_t>(dstBase) - 0x20 + count * 0x20); // Point to last destination slot
    
    // Temporary stack buffer (possibly for swapping data)
    PacketEntry temp;
    PacketEntry* tempPtr = &temp; // local_10 points to stack buffer
    PacketEntry* unknownPtr = nullptr; // local_14, initialized later
    
    while (count != 0) {
        count--;
        // Call destructor on the source entry (one before srcEnd)
        packetEntryDestructor(srcEnd - 1);
        // Perform some general state cleanup
        connectionCleanup();
        
        // Free temporary buffer if it was allocated (not stack and not null)
        if (unknownPtr != tempPtr && unknownPtr != nullptr) {
            g_freePtr(unknownPtr);
        }
        
        // Copy the last 4 bytes from source entry to destination entry
        dst->dwordAt1C = (srcEnd - 1)->dwordAt1C;
        
        // Move pointers backwards
        dst = reinterpret_cast<PacketEntry*>(reinterpret_cast<uint32_t>(dst) - 0x20);
        srcEnd = reinterpret_cast<PacketEntry*>(reinterpret_cast<uint32_t>(srcEnd) - 0x20);
    }
    
    return dst; // Points to the entry before the first moved one (or base-0x20)
}