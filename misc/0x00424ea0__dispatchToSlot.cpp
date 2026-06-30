// FUNC_NAME: dispatchToSlot
uint __thiscall dispatchToSlot(int* this, uint id, /* unused */ uint unused, uint eventData)
{
    uint slotIndex = getSlotIndex(id);
    if (slotIndex < 4) {
        // +0x10: pointer to array of slot objects (each 0x1d0 bytes)
        int* slotPtr = *(int**)((char*)this + 0x10) + (slotIndex * 0x1d0);
        uint result = processSlot(slotPtr, eventData, id);
        return result;
    }
    // Invalid slot index: return high bits of id as error
    return slotIndex & 0xffffff00;
}