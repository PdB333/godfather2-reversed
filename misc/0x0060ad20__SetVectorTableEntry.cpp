// FUNC_NAME: SetVectorTableEntry
void SetVectorTableEntry(uint index, const float* newVector)
{
    // Check if index is non-zero (note: index of 0 is skipped? Possibly intentional)
    if (index == 0) return;

    uint slotIndex = index & 0xFF;           // Lower 8 bits determine slot (0-255)
    float* tableEntry;                        // Pointer to the selected vector in memory

    // Choose which global table to use based on the sign of index
    // Positive or zero -> g_positiveVectorTable, negative -> g_negativeVectorTable
    if ((int)index >= 0)                      // (index & 0x80000000) == 0
    {
        // Each table entry is 0x10 bytes (4 floats), stride * slotIndex
        tableEntry = (float*)((uintptr_t)&g_positiveVectorTable + slotIndex * 0x10);
    }
    else
    {
        tableEntry = (float*)((uintptr_t)&g_negativeVectorTable + slotIndex * 0x10);
    }

    float oldX = tableEntry[0];
    float newX = newVector[0];
    if (oldX != newX)
    {
        tableEntry[0] = newX;
    }

    float oldY = tableEntry[1];
    float newY = newVector[1];
    if (oldY != newY)
    {
        tableEntry[1] = newY;
    }

    float oldZ = tableEntry[2];
    float newZ = newVector[2];
    if (oldZ != newZ)
    {
        tableEntry[2] = newZ;
    }

    // If any component changed, notify the manager (via vtable call)
    if (oldZ != newZ || oldY != newY || oldX != newX)
    {
        if ((int)index < 0)                   // Negative index -> call method at vtable+0x178
        {
            (**(code**)(*DAT_01205750 + 0x178))(); // No arguments? Usually this is a callback or event
        }
        else                                  // Non-negative index -> call method at vtable+0x1b4 with params
        {
            (**(code**)(*DAT_01205750 + 0x1b4))(DAT_01205750, slotIndex, tableEntry, 1);
        }
    }
}