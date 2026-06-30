// FUNC_NAME: SimManager::activateSlot
bool __thiscall SimManager::activateSlot(uint slotIndex, int mode)
{
    char isValid;
    int slotBase;
    int entryPtr;
    int objectPtr;

    if (mode == 1) {
        isValid = this->isValidSlotIndex(slotIndex);
        if (isValid != '\0') {
            // Inline slot array starts at this+0x10, each slot is 0x30 bytes
            slotBase = 0;
            if (slotIndex < 0x200) {
                slotBase = slotIndex * 0x30 + 0x10 + (int)this;
            }
            // Zero out fields at offsets 0x10, 0x18, 0x20, 0x2c within the slot
            *(int *)(slotBase + 0x20) = 0;
            *(int *)(slotBase + 0x18) = 0;
            *(int *)(slotBase + 0x2c) = 0;
            *(int *)(slotBase + 0x10) = 0;
            return true;
        }
    }
    else if (*(int *)((int)this + 0x603c) != 0) {
        // Dynamic slot array at this+0x603c, each slot is 0x74 bytes
        if ((0x1ff < slotIndex) ||
            (slotBase = slotIndex * 0x74 + *(int *)((int)this + 0x603c), slotBase == 0)) {
            return false;
        }
        entryPtr = *(int *)(slotBase + 8);
        if ((entryPtr != 0) &&
           (*(int *)(entryPtr + 8) != 0 && 
            (this->getGlobalState(0), *(int *)(entryPtr + 0x68) != 5))) {
            return true;
        }
        // Fallback to inline slot path
        return this->activateSlot(slotIndex, 1);
    }
    return false;
}