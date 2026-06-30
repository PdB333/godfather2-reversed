// FUNC_NAME: registerPair
// Function address: 0x006141f0
// Registers a pair of values (param1, param2) into a global slot array.
// Returns slot index (0-3) on success, -1 if all slots are used.

struct SlotEntry {
    int param1;     // +0x00
    int param2;     // +0x04
    char active;    // +0x08 (1 if slot is occupied)
    char padding[3]; // +0x09
};

static SlotEntry g_slotArray[4]; // Address 0x011f6bb8, size 0x30

int __cdecl registerPair(int param1, int param2)
{
    for (int i = 0; i < 4; i++)
    {
        if (g_slotArray[i].active == 0)
        {
            g_slotArray[i].param1 = param1;
            g_slotArray[i].param2 = param2;
            g_slotArray[i].active = 1;
            return i;
        }
    }
    return -1;
}