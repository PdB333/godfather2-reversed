// FUNC_NAME: SimNpc::resetWeaponSlots
void SimNpc::resetWeaponSlots(void)
{
    // +0x180: pointer to SimManager or similar
    int* pManager = *(int**)(this + 0x180);
    int* pArrayContainer = *(int**)(this + 4);   // +4: dynamic array structure (count, capacity, data)
    int* pSlot1 = *(int**)(this + 0x50);          // +0x50: first weapon/item slot
    int* pSlot2 = *(int**)(this + 0x54);          // +0x54: second weapon/item slot
    int* pArrayBase;

    // Clear slot1 if occupied
    if (pSlot1 != 0) {
        // Object header: at -8 is its index into the container array
        int index = *(int*)(pSlot1 - 8);
        pArrayBase = *(int**)(pArrayContainer + 0xc); // +0xc: pointer to array of object pointers
        pArrayBase[index] = 0;                        // Remove pointer from container
        pArrayContainer[1]--;                         // +4: decrement count
        // Free the chunk (header at -0x10)
        (*DAT_01206694)(pSlot1 - 0x10);
    }
    *(int**)(this + 0x50) = 0;                        // Clear slot1

    // Clear slot2 if occupied
    if (pSlot2 != 0) {
        int index2 = *(int*)(pSlot2 - 8);
        pArrayBase = *(int**)(pArrayContainer + 0xc);
        pArrayBase[index2] = 0;
        pArrayContainer[1]--;
        (*DAT_01206694)(pSlot2 - 0x10);
    }
    *(int**)(this + 0x54) = 0;                        // Clear slot2

    // Possibly allocate a new weapon from manager logic
    int* pWeaponData = 0;
    if (pManager != 0) {
        int* pWeaponDefData = *(int**)(pManager + 0x20); // +0x20: weapon definition table?
        if (pWeaponDefData != 0) {
            if (*(int*)(pWeaponDefData + 0xf8) != 0) {  // +0xf8: flag or count?
                pWeaponData = (int*)FUN_0067b8a0();      // Function that creates/allocates a weapon
            }
        }
        *(int**)(this + 0x50) = pWeaponData;             // Assign to slot1
    }
    return;
}