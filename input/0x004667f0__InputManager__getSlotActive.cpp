// FUNC_NAME: InputManager::getSlotActive
// Function at 0x004667f0: checks active flag for a controller slot (0-15) or all slots (index 0x11).
// The slot data is stored as an array of 0x168-byte structures at offset 0x174 in the InputManager object.
// The first byte of each structure indicates active (non-zero) or inactive (zero).
// __fastcall: ECX = slotIndex (byte), EDX = this pointer
__fastcall byte InputManager::getSlotActive(byte slotIndex) const
{
    // Pointer to the array of 16 slot structures at this+0x174
    const byte* slotArray = reinterpret_cast<const byte*>(
        reinterpret_cast<const char*>(this) + 0x174);

    // Index 0x00-0x0F: return the first byte of the corresponding slot structure
    if (slotIndex < 0x10)
    {
        // Each slot structure is 0x168 bytes long
        return slotArray[slotIndex * 0x168];
    }

    // Special index 0x11: return 1 if ALL 16 slots have non‑zero first byte
    if (slotIndex == 0x11)
    {
        byte result = 1; // assume all active
        for (int i = 0; i < 0x10; ++i)
        {
            if (slotArray[i * 0x168] == 0)
            {
                result = 0;
                break; // early exit found
            }
        }
        return result;
    }

    // Invalid index: return 0
    return 0;
}