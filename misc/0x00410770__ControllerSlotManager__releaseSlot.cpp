// FUNC_NAME: ControllerSlotManager::releaseSlot
void ControllerSlotManager::releaseSlot(byte slotIndex) {
    // Get the pointer from the slot array at offset +0x4ec (slotIndex * 4)
    void* slotObj = *(void**)((uint)this + 0x4ec + slotIndex * 4);
    
    if (slotObj != nullptr) {
        // Call the first virtual function (likely a release/destructor) with argument 1
        (*(void(__thiscall**)(void*, int))slotObj)(slotObj, 1);
        
        // Null out the slot pointer
        *(void**)((uint)this + 0x4ec + slotIndex * 4) = nullptr;
        
        // If this slot is the current "active slot" (offset +0x565), reset it to invalid (0x12)
        if (slotIndex == *(byte*)((uint)this + 0x565)) {
            *(byte*)((uint)this + 0x565) = 0x12; // 0x12 = INVALID_SLOT
            return;
        }
        
        // Otherwise, if it's the "last used slot" (offset +0x564), reset that too
        if (slotIndex == *(byte*)((uint)this + 0x564)) {
            *(byte*)((uint)this + 0x564) = 0x12;
        }
    }
}