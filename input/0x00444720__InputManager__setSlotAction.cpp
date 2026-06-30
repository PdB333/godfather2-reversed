// FUNC_NAME: InputManager::setSlotAction
// Function address: 0x00444720
// Sets or clears an action binding for a controller slot (0-15).
// If param_3 (actionId) is non-zero and param_4 (slotFlag) is non-zero, enables the binding.
// Otherwise, disables it.

void __thiscall InputManager::setSlotAction(int this, uint slotIndex, int actionId, char slotFlag)
{
    if (slotIndex < 0x10)
    {
        // Each slot entry is 0x18 bytes, starting at this+0x14
        int* slotEntry = reinterpret_cast<int*>(this + 0x14 + slotIndex * 0x18);
        if (slotEntry != 0)
        {
            if ((actionId != 0) && (slotFlag != 0))
            {
                // Set flag bit 3 (0x8) to mark as active
                *(uint*)(slotEntry + 2) |= 8;   // offset +8 (uint flags)
                *(int*)(slotEntry + 5) = 0x01205210 + actionId; // offset +0x14: action/handler pointer
                *(char*)(slotEntry + 4) = slotFlag; // offset +0x10: slot flag byte
                return;
            }
            // Clear the binding
            *(uint*)(slotEntry + 2) &= ~8;      // clear flag bit 3
            *(int*)(slotEntry + 5) = 0;         // zero action pointer
            *(char*)(slotEntry + 4) = 0;        // zero slot flag
        }
    }
    return;
}