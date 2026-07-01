// FUNC_NAME: SlotManager::getSlot

// Reconstructed from 0x0083fa50
// Returns a pointer to the slot at the given index, or nullptr if out of range.
// Each slot is 0x10 bytes. Count stored at +0x50, array pointer at +0x58.
void* __thiscall SlotManager::getSlot(int index) {
    if (index >= 0 && index < *(int*)((char*)this + 0x50)) {
        return (void*)(*(int*)((char*)this + 0x58) + index * 0x10);
    }
    return nullptr;
}