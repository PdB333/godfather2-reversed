// FUNC_NAME: SlotManager::setCurrentSlot
void __thiscall SlotManager::setCurrentSlot(uint slotIndex)
{
    // Validate slot index against the count stored in the manager at this+0x20, field +0xa8
    if (slotIndex < *(uint *)(*(int *)(this + 0x20) + 0xa8) && 
        // Check if the slot actually changed (current stored at this+0x40)
        *(uint *)(this + 0x40) != slotIndex)
    {
        *(uint *)(this + 0x40) = slotIndex;
        // Notify/update internal state
        FUN_004d3d90();
    }
}