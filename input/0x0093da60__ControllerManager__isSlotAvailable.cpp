// FUNC_NAME: ControllerManager::isSlotAvailable
bool __thiscall ControllerManager::isSlotAvailable(int thisPtr, uint index)
{
    // +0x0c: mNumSlots (uint) – total number of slots
    // +0x10: mMaxActiveSlots (ushort) – maximum active slots allowed
    // +0x12: mActiveSlotCount (ushort) – current number of active slots

    // Returns 0 (false) if the slot exists and there is capacity, 1 (true) otherwise.
    if (((*(uint *)(thisPtr + 0x0c) == 0) || (index < *(uint *)(thisPtr + 0x0c))) &&
        ((*(ushort *)(thisPtr + 0x10) == 0) || (*(ushort *)(thisPtr + 0x12) < *(ushort *)(thisPtr + 0x10))))
    {
        return false; // slot is available
    }
    return true;  // slot not available (invalid index or at capacity)
}