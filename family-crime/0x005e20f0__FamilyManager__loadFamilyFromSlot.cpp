// FUNC_NAME: FamilyManager::loadFamilyFromSlot
bool __thiscall FamilyManager::loadFamilyFromSlot(uint slotIndex, int* presetArrayBase) {
    // slotIndex must be < 5 (number of families)
    if (slotIndex < 5) {
        char* pEntry = (char*)presetArrayBase + slotIndex * 0x4A4; // +0x4A4 per family preset
        // Copy data from preset to this family object
        *(byte*)(this + 0x14) = *(byte*)(pEntry + 0x494);  // +0x494: some byte field (e.g., bool)
        *(int*)(this + 0x18) = *(int*)(pEntry + 0x210);    // +0x210: some int field
        // Call helper to copy sub-object at offset +0x498 within preset
        helperCopyFamilyData(pEntry + 0x498);               // FUN_004d3e20
        *(int*)(this + 0x10) = *(int*)(pEntry + 0x490);    // +0x490: some int field
        *(int*)(this + 0x1c) = *(int*)(pEntry + 0x1f8);    // +0x1f8: another int field
    }
    return slotIndex < 5;
}