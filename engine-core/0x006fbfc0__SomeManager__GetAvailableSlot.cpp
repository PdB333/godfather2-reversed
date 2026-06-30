// FUNC_NAME: SomeManager::GetAvailableSlot
void __thiscall SomeManager::GetAvailableSlot(void* pSlotOutput, uint32_t* pIndexOutput) {
    // Check if output pointer is valid
    if (pSlotOutput == nullptr) {
        return;
    }

    // Slot structures: offset +0x180 (slot0), +0x1b8 (slot1)
    // Slot flags at +0x198 (slot0 in use), +0x1d0 (slot1 in use)
    // Each slot is 0x38 bytes, flag at +0x18 from slot start

    // Check first slot (index 0)
    if (*(int*)((char*)this + 0x198) == 0) {
        *(void**)(pSlotOutput) = (void*)((char*)this + 0x180);
        *pIndexOutput = 0;
        return;
    }

    // Check second slot (index 1)
    if (*(int*)((char*)this + 0x1d0) == 0) {
        *(void**)(pSlotOutput) = (void*)((char*)this + 0x1b8);
        *pIndexOutput = 1;
    }
}