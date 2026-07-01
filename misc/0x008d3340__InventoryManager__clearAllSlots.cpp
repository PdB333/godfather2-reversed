// FUNC_NAME: InventoryManager::clearAllSlots
void __fastcall InventoryManager::clearAllSlots(int this)
{
    // Dynamic array of item slots (each 0x18 bytes)
    // +0x18: pointer to slot array (type unknown)
    // +0x1c: number of slots in dynamic array
    uint slotCount = *(uint *)(this + 0x1c);
    if (slotCount != 0) {
        char* slotArrayBase = *(char **)(this + 0x18);
        for (uint i = 0; i < slotCount; i++) {
            // Clear field at offset +4 within each slot (e.g., item ID or pointer)
            *(int *)(slotArrayBase + i * 0x18 + 4) = 0;
        }
    }

    // Static array of 5 quick-use slots (each 0x14 bytes)
    // Clear the first int (offset 0) of each quickslot
    *(int *)(this + 0x24) = 0; // quickslot[0] first field
    *(int *)(this + 0x38) = 0; // quickslot[1]
    *(int *)(this + 0x4c) = 0; // quickslot[2]
    *(int *)(this + 0x60) = 0; // quickslot[3]
    *(int *)(this + 0x74) = 0; // quickslot[4]
}