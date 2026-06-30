// FUNC_NAME: SlotManager::findSlotByID
// Address: 0x0044c8c0
// Role: Looks up a slot by ID from an internal array (3 slots), returns pointers to associated global data tables.
// The class has an array of slot IDs at this+0x30 (3 ints). On match, outputs pointers to two global arrays
// (stride 0x84 and 0x210) and returns a handle encoding the second pointer low byte set to 1. On failure returns 0x300.

extern int g_slotData1[];   // Base: DAT_01163834, stride 0x84 (132 bytes)
extern int g_slotData2[];   // Base: DAT_01163650, stride 0x210 (528 bytes)

uint __thiscall SlotManager::findSlotByID(int slotID, int* outPtr1, int* outPtr2)
{
    int* slotIDs = (int*)((char*)this + 0x30); // +0x30: array of 3 int slot IDs

    for (int i = 0; i < 3; i++)
    {
        if (slotIDs[i] == slotID)
        {
            // Compute pointers into the global tables based on the slot index
            *outPtr1 = &g_slotData1[i * 0x84 / sizeof(int)];   // actually byte offset 0x84
            *outPtr2 = &g_slotData2[i * 0x210 / sizeof(int)];  // actually byte offset 0x210

            // Return value: encodes the address of the second table entry with low byte set to 1 (success flag)
            uint32_t addr = (uint32_t)(*outPtr2);
            return (addr & 0xFFFFFF00) | 1;
        }
    }

    // No match: return 0x300 (i.e., 3 << 8, with low byte 0)
    return 0x300;
}