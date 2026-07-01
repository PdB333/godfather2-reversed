// FUNC_NAME: AnimationSlotManager::setSlotType
// Function address: 0x008ddca0
// Sets a slot's type field and conditionally triggers an action based on the second field.
// The array of slots is stored via a pointer at this+0x24, each slot is 12 bytes (3 * uint32).

bool __thiscall AnimationSlotManager::setSlotType(uint slotIndex)
{
    if (slotIndex > 0x18)
        return false;

    // Get pointer to the slot structure: base + slotIndex * 12
    // base = *(uint32*)(this + 0x24)  (pointer to array)
    uint32* slot = reinterpret_cast<uint32*>(*(uint32*)(this + 0x24)) + slotIndex * 3;

    // Set the first field (type) to 3
    slot[0] = 3;

    // If the second field is non-zero and not 0x48, call an action routine
    if (slot[1] != 0 && slot[1] != 0x48)
    {
        // FUN_008dd2c0(3) – likely triggers animation or state transition
        doSlotAction(3);
    }

    return true;
}