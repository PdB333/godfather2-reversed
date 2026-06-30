// FUNC_NAME: SimManager::releaseSlot
int __thiscall SimManager::releaseSlot(SimManager* this, int obj, int slotIndex) {
    // Calculate offset into slot array (each slot is 20 bytes)
    int slotPtr = reinterpret_cast<int>(this) + (slotIndex * 5 + 5) * 4;
    int* slotBase = reinterpret_cast<int*>(slotPtr);

    // Slot +0x4 = pointer to an object (or zero if empty)
    int objectPtr = slotBase[1];
    if (objectPtr != 0) {
        int derivedObj = objectPtr - 0x48; // Adjust pointer to derived object (e.g., remove base offset)
        if (derivedObj != 0) {
            // Check if object is flagged for removal (bit 0 at obj+0x1d4)
            if (*(reinterpret_cast<unsigned char*>(obj) + 0x1d4) & 1) {
                // Call handler for object removal from slot
                FUN_00705100(derivedObj, obj, slotPtr);
                // Clear the corresponding bit in the active slots mask
                *(reinterpret_cast<unsigned int*>(this) + 0x114) &= ~(1 << (slotIndex & 0x1f));
                return 1; // Slot released
            }
            // Compare object type ID (at obj+0x1ad) with expected type in slot (at objectPtr+0x165)
            if (*(reinterpret_cast<char*>(obj) + 0x1ad) != *(reinterpret_cast<char*>(objectPtr) + 0x165)) {
                // Call type mismatch handler
                FUN_00705030(obj, derivedObj, slotPtr);
            }
            return 0; // Slot not released
        }
    }

    // Slot is empty or pointed to null derived object: perform cleanup on obj
    FUN_00704ca0(obj);

    // Adjust slot count based on max count (slot+0x10)
    unsigned int maxCount = *(reinterpret_cast<unsigned int*>(slotBase + 0x10 / 4)); // offset 0x10
    if (maxCount < 2) {
        *(reinterpret_cast<unsigned int*>(slotBase + 0xc / 4)) = maxCount; // slot+0xc = count
    } else {
        *(reinterpret_cast<unsigned int*>(slotBase + 0xc / 4)) = 1;
    }

    // Call generic engine updates
    FUN_00704590(obj);
    FUN_00707610();
    FUN_00707ea0();

    // Clear the slot's active bit
    *(reinterpret_cast<unsigned int*>(this) + 0x114) &= ~(1 << (slotIndex & 0x1f));
    return 1;
}