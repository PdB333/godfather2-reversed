// FUNC_NAME: ClientManager::findOrCreateEntity
int __thiscall ClientManager::findOrCreateEntity(int slotIndex, unsigned short entityID) {
    // slotIndex: from low byte of ECX (masked 0xFF)
    // entityID: ushort parameter
    // Calculate pointer to slot entry (size 0x168 each, array at offset 0x10 from this)
    int* slotEntry = (int*)((char*)this + 0x10 + (slotIndex & 0xFF) * 0x168);
    
    // First DWORD of slotEntry points to a data block
    int* dataBlock = (int*)*slotEntry;
    
    // entityID * 0x80 offsets into an array at dataBlock[0xBC / 4] (offset +0xBC)
    int* entityEntry = (int*)(*(int*)((char*)dataBlock + 0xBC) + entityID * 0x80);
    
    // Compare first DWORD of entityEntry with 4 IDs stored at this+0x18BC
    int* teamIDList = (int*)((char*)this + 0x18BC);
    for (int i = 0; i < 4; i++) {
        if (*entityEntry == teamIDList[i]) {
            return 1; // Entity found and matches one of the team IDs
        }
    }
    
    // Entity not found in team, call a function to create or assign
    // FUN_00465850(0, slotEntry[0x56], slotEntry[0x56], slotEntry + 0x16, entityEntry + 0xB, entityEntry + (char)entityEntry[1] * 3 + 8)
    return FUN_00465850(
        0,
        slotEntry[0x56],                                   // offset 0x158 from slot start
        slotEntry[0x56],                                   // same value
        slotEntry + 0x16,                                  // offset 0x58 from slot start
        (int*)((char*)entityEntry + 0xB * 4),              // offset 0x2C from entity
        (int*)((char*)entityEntry + (char)entityEntry[1] * 3 * 4 + 8) // complex offset based on byte field
    );
}