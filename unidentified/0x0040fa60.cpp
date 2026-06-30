// Function address: 0x0040fa60
// Identified role: Checks if a controller slot is active (occupied).
// The class has an array of 16 controller slots starting at offset +0x6a,
// each slot of size 0x44 bytes. The first byte of each slot is a boolean
// indicating whether the slot is in use (non-zero).
// Special index 0x11 (17) checks if all 16 slots are occupied.

bool __thiscall IsControllerSlotActive(void* this_ptr, unsigned char slotIndex)
{
    // Array of 16 slots, each 0x44 bytes, starting at offset +0x6a
    char* slotArray = reinterpret_cast<char*>(this_ptr) + 0x6a; // +0x6a: start of slot array

    if (slotIndex == 0x11)
    {
        unsigned int count = 0;
        char* currentSlot = slotArray;
        do
        {
            if (*currentSlot == '\0') // Slot is empty
            {
                // Return 0 (low byte cleared) – since count < 256, result is 0
                return static_cast<bool>(count & 0xffffff00);
            }
            count++;
            currentSlot += 0x44;
        } while (static_cast<int>(count) < 16);

        // All slots occupied, return 1
        return true;
    }

    // For specific slot index (0-15)
    if (slotIndex < 0x10)
    {
        // Check if that slot's active flag is non-zero
        char* specificSlot = slotArray + (slotIndex * 0x44);
        return (*specificSlot != '\0');
    }

    return false;
}