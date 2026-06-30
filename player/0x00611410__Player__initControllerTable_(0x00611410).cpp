// FUNC_NAME: Player::initControllerTable (0x00611410)
// Initializes 20 controller slots from a global table and zeros various flag fields
void __fastcall Player::initControllerTable(Player* thisObj) {
    // Starting address of global pointer table (20 entries, each 12 bytes)
    undefined** tablePtr = &PTR_PTR_01128494;
    // Write destination for slot data: second array at this+0x190, first array at this+0x17C
    int* slotData = (int*)((uint)thisObj + 0x190);
    
    do {
        int valA;
        if (*tablePtr == nullptr) {
            valA = 0;
        } else {
            valA = FUN_0060a2e0(*tablePtr);  // retrieves a resource/handle from the pointer
        }
        *(slotData - 5) = valA;         // Stored at this+0x17C + (i*4)  (first array)
        *slotData = FUN_0060a380();     // Retrieves a global value (second array at this+0x190 + (i*4))
        
        tablePtr += 3;  // Advance by 12 bytes (3 pointers) to next table entry
        slotData++;
    } while ((int)tablePtr < (int)0x1128584);  // Loop until all 20 entries processed
    
    // Zero out various flags and counters
    *(int*)((uint)thisObj + 0xa4) = 0;   // +0xa4: some state
    *(int*)((uint)thisObj + 0xc0) = 0;   // +0xc0: slot timer
    *(int*)((uint)thisObj + 0xf0) = 0;   // +0xf0: interaction flag
    *(int*)((uint)thisObj + 0xfc) = 0;   // +0xfc: pending action
    *(int*)((uint)thisObj + 0x104) = 0;  // +0x104: lock flag
    *(int*)((uint)thisObj + 0x10c) = 0;  // +0x10c: retry count
    *(int*)((uint)thisObj + 0x114) = 0;  // +0x114: target index
    *(int*)((uint)thisObj + 0x11c) = 0;  // +0x11c: state timer
    *(int*)((uint)thisObj + 0x120) = 0;  // +0x120: sub-state
    *(int*)((uint)thisObj + 0x12c) = 0;  // +0x12c: current slot id (300 decimal)
    *(int*)((uint)thisObj + 0x1e0) = 0;  // +0x1e0: extra flags
    *(int*)((uint)thisObj + 0x1e4) = 0;  // +0x1e4: more flags
}