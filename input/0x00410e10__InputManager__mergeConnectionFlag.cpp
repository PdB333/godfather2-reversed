// FUNC_NAME: InputManager::mergeConnectionFlag
// Address: 0x00410e10
// This function checks the current slot state and merges a flag into the input bits.
// Calling convention: __fastcall (this in ECX, inputFlags in EAX)
uint InputManager::mergeConnectionFlag(uint inputFlags)
{
    // +0x564: current slot index (byte, 0-15)
    uint uSlotIndex = *(byte*)(this + 0x564);
    if (uSlotIndex < 0x10)
    {
        // +0x52d: array of 16 per-slot flags (bytes)
        byte* slotFlags = (byte*)(this + 0x52d);
        if (slotFlags[uSlotIndex] != 0)
        {
            // +0x560: pointer to slot data
            bool bConnected = (*(int*)(this + 0x560) != 0);
            return bConnected ? 1 : 0;
        }
    }
    // Keep only bits 8-10 from the input (original 3-bit field)
    return inputFlags & 0x700;
}