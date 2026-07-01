// FUNC_NAME: SlotManager::resolveSlotIndex
int __thiscall SlotManager::resolveSlotIndex(int this, int slotIndex) {
    // Access slot at offset 0xC8 from this, each slot 0x38 (56) bytes
    Slot* slot = reinterpret_cast<Slot*>(this + 0xC8 + slotIndex * 0x38);
    
    // Define known magic hash pattern for an initialized slot (128 bits)
    const int magicHash[4] = {
        0xBAEDBDBA, // -0x45245246
        0xBEEFBEEF, // -0x41104111
        0xEAC15A55, // -0x153ea5ab
        0x91100911  // -0x6eeff6ef
    };
    
    // Check if the slot is either empty (type == 0) or pending (type == 0x48)
    bool typeEmptyOrPending = (slot->type == 0 || slot->type == 0x48);
    
    // Check if the signature is not the magic hash and not all zeros
    bool sigNotMagic = !(slot->sig[0] == magicHash[0] && 
                         slot->sig[1] == magicHash[1] && 
                         slot->sig[2] == magicHash[2] && 
                         slot->sig[3] == magicHash[3]);
    bool sigNotZero  = !(slot->sig[0] == 0 && slot->sig[1] == 0 && 
                         slot->sig[2] == 0 && slot->sig[3] == 0);
    
    // If slot is in an uninitialized but valid state, construct the slot object
    if (typeEmptyOrPending && sigNotMagic && sigNotZero) {
        // Factory/allocator call (FUN_00446100) – returns an object pointer
        int objPtr = FUN_00446100(slot, 0);
        if (objPtr != 0) {
            // Constructor/initializer (FUN_0078d030)
            FUN_0078d030(objPtr);
        }
    }
    
    // Return the object pointer derived from type field, or null
    if (slot->type != 0) {
        return slot->type - 0x48;
    }
    return 0;
}

// Slot structure (unpacked from decompiled, size 0x38)
struct Slot {
    int sig[4];    // +0x00: 128-bit signature (hash or GUID)
    int type;      // +0x10: type/status field (0 = empty, 0x48 = pending)
    char data[36]; // +0x14: remaining 36 bytes (0x38 - 0x14)
};