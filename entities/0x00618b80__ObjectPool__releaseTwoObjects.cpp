// FUNC_NAME: ObjectPool::releaseTwoObjects
void __fastcall ObjectPool::releaseTwoObjects(uint slotIndex1, uint slotIndex2) {
    // Global array of slots (base address 0x011a0f28), each slot 0x38 bytes.
    // Slot structure: offset +0x14 is a pointer to an object with vtable.
    static const uint kSlotElementCount = 0x1000;
    static const uint kSlotSize = 0x38;
    static const uint kPointerOffset = 0x14; // offset of the object pointer within a slot

    // Validate indices and get slot pointers
    Slot* slot1 = (slotIndex1 < kSlotElementCount) ? &g_slotArray[slotIndex1] : nullptr;
    Slot* slot2 = (slotIndex2 < kSlotElementCount) ? &g_slotArray[slotIndex2] : nullptr;

    if (slot1 && slot2) {
        // Each slot contains a pointer to an object with a vtable.
        // Virtual function at vtable+0x48 is the "release" or "destroy" method.
        void* obj1 = *(void**)((char*)slot1 + kPointerOffset);
        void* obj2 = *(void**)((char*)slot2 + kPointerOffset);

        // Call release on both objects
        if (obj1) {
            (*(void(__thiscall**)(void*))(*(uint32*)obj1 + 0x48))(obj1);
        }
        if (obj2) {
            (*(void(__thiscall**)(void*))(*(uint32*)obj2 + 0x48))(obj2);
        }
    }
    // Note: The original assembly contains a meaningless local destruction block
    // (likely dead code or decompilation artifact) which is omitted here.
}