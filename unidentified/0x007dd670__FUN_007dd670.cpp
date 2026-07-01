// FUNC_NAME: SomeManager::resetSlotArray
// Function at 0x007dd670: Initializes an array of 27 slots (each 28 bytes) with default values.
// The array starts at offset +0x8 from 'this'. Each slot has a byte flag at offset 0, and three ints at offsets 4, 8, 12.
// The slot count is stored at offset +0x2F4 (set to 27).
void __fastcall SomeManager::resetSlotArray(int thisPtr)
{
    // Slot structure (28 bytes each)
    // Offset 0: byte m_active (set to 1)
    // Offset 4: int m_field1 (set to 0)
    // Offset 8: int m_field2 (set to 0)
    // Offset 12: int m_field3 (set to 0)
    // Offsets 16-27: unused padding

    // Pointer to the start of the slot array (at this+0x8)
    int* slotBase = reinterpret_cast<int*>(thisPtr + 8);

    // Number of slots to initialize (27)
    int slotCount = 0x1b; // 27

    // Loop through each slot (do-while, runs 27 times)
    int i = 0x1a; // 26, but loop runs 27 times due to do-while
    do {
        // Each slot is 28 bytes (7 ints). The slot's base is slotBase - 2 ints? 
        // Actually, the code writes to offsets -8, -4, 0, +4 relative to the current pointer.
        // We interpret the slot structure as starting at (current pointer - 8).
        // So we adjust: the slot's m_active is at current pointer - 8.
        // But for clarity, we'll write directly using the known offsets.

        // Set byte at slotBase - 8 to 1 (m_active)
        *reinterpret_cast<unsigned char*>(slotBase - 2) = 1; // slotBase - 2 ints = -8 bytes

        // Set int at slotBase - 4 to 0 (m_field1)
        *(slotBase - 1) = 0;

        // Set int at slotBase + 0 to 0 (m_field2)
        *slotBase = 0;

        // Set int at slotBase + 4 to 0 (m_field3)
        *(slotBase + 1) = 0;

        // Move to next slot (28 bytes forward)
        slotBase += 7; // 7 ints = 28 bytes
        i--;
    } while (i >= 0); // Loop runs for i = 26 down to 0 inclusive (27 iterations)

    // Store the slot count at offset +0x2F4 (inside the last slot's padding)
    *reinterpret_cast<int*>(thisPtr + 0x2f4) = 0x1b; // 27
}