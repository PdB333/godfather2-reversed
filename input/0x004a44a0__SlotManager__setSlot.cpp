// FUNC_NAME: SlotManager::setSlot
bool SlotManager::setSlot(int id, void* object) {
    if (id == 0 || object == nullptr) {
        return false;
    }

    uint32_t slotCount = *(uint32_t*)(this + 0x6C);
    if (slotCount == 0) {
        return false;
    }

    int* slotArray = *(int**)(this + 0x68);  // array of Slot structures (16 bytes each)
    for (uint32_t i = 0; i < slotCount; i++) {
        int* slot = slotArray + i * 4;  // each slot: [id, flags, data1, data2]
        if (slot[0] == id) {            // id match
            // Allocate a new slot (likely 16 bytes)
            uint32_t* newSlot = reinterpret_cast<uint32_t*>(FUN_004a7c70());
            if (newSlot == nullptr) {
                return false;
            }

            newSlot[0] = reinterpret_cast<uint32_t>(object);  // store object pointer
            newSlot[2] = slot[2];                              // copy data1
            newSlot[3] = slot[3];                              // copy data2

            FUN_004a62b0();  // additional initialization

            // Check if the original slot had the "callback" flag (bit 1)
            uint16_t originalFlags = *(uint16_t*)(slot + 1); // flags at byte offset 4
            if ((originalFlags & 2) != 0) {
                // Call virtual function at offset 0x24 of the object
                (*(void (**)())(*(uint32_t*)object + 0x24))();
                // Set the same flag in the new slot
                *(uint16_t*)(newSlot + 1) |= 2;
            }

            FUN_004a67a0();  // finalization
            return true;
        }
    }
    return false;
}