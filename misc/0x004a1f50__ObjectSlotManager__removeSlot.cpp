// FUNC_NAME: ObjectSlotManager::removeSlot
void ObjectSlotManager::removeSlot(uint index) {
    // Array of 3 slots (each 8 bytes) starts at this+0x12C
    // Slot layout: +0x00 void* object, +0x04 byte activeFlag
    struct Slot {
        void* object;  // +0x00
        byte active;   // +0x04
        // padding to 8 bytes? Actually the next field is at +0x04, but the loop copies 2 uint32s per slot, so the active byte is part of the second uint32.
        // So Slot is 8 bytes: [object (4), active (1), pad (3)] or [object (4), active+3pad (4)].
    };

    Slot* slots = reinterpret_cast<Slot*>(reinterpret_cast<byte*>(this) + 0x12C);
    Slot* currentSlot = &slots[index];
    void* obj = currentSlot->object;

    if (obj != nullptr) {
        if (currentSlot->active != 0) {
            // Call first virtual function of the object with argument 1
            (*(void(__thiscall**)(void*, int))(*(int*)obj))(obj, 1);
        }
        currentSlot->object = nullptr;  // Clear pointer
    }

    // Shift remaining slots left to fill the gap (if not last slot)
    if (index < 3) {
        Slot* src = currentSlot + 1;
        uint count = (3 - index) * 2;  // Number of uint32s to copy (2 per slot)
        uint* dest = reinterpret_cast<uint*>(currentSlot);
        uint* src32 = reinterpret_cast<uint*>(src);
        for (uint i = count; i != 0; i--) {
            *dest = *src32;
            dest++;
            src32++;
        }
    }

    // Zero out field at this+0x144 (likely a count or last‑slot marker)
    *reinterpret_cast<uint*>(reinterpret_cast<byte*>(this) + 0x144) = 0;
}