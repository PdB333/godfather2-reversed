// FUNC_NAME: PoolManager::addSlot
// Address: 0x00625340
// Role: Adds a new slot entry to a fixed-size pool (max 32 slots). Each slot stores three integer values.
// The pool structure has:
//   +0x00: count (int)
//   +0x04: firstArray[32] (int)  — param2
//   +0x84: secondArray[32] (int) — param3
//   +0x104: thirdArray[32] (int) — param4
//   +0x184: used[32] (char)      — slot occupancy flag

void __thiscall PoolManager::addSlot(int param2, int param3, int param4)
{
    unsigned int slotIndex = 0;

    // Find first free slot (used == 0)
    while (true)
    {
        if (slotIndex > 31) // 0x1f
        {
            return; // No free slot, exit
        }
        if (this->used[slotIndex] == '\0')
        {
            break;
        }
        slotIndex++;
    }

    // Mark slot as used
    this->used[slotIndex] = 1;

    // Store three integer parameters in parallel arrays
    this->firstArray[slotIndex] = param2;   // offset +0x04 + slotIndex*4
    this->secondArray[slotIndex] = param3;  // offset +0x84 + slotIndex*4
    this->thirdArray[slotIndex] = param4;   // offset +0x104 + slotIndex*4

    // Increment total count
    this->count++; // offset +0x00
}