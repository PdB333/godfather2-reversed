// FUNC_NAME: NetSession::initSlotArray
// Function at 0x006142d0: Initializes a global array of slot structures (4 slots, each 12 bytes), likely for reliable packet windows or ghost replication.
// Constants: DAT_00e2b1a4 = some default value, DAT_011f6bbc = start of slot array, final two ints at 0x11f6be8/0x11f6bec set to -1 as sentinel.

extern int DAT_00e2b1a4;         // global constant
extern int DAT_011f6bbc;         // start of slot array (base of first element? See below)
extern int _DAT_011f6be8;        // last slot fields
extern int _DAT_011f6bec;        

void __cdecl initSlotArray(void)
{
    int constant = DAT_00e2b1a4;
    int* pSlot = &DAT_011f6bbc;   // Pointer to start of each slot's "offset 0" field
    
    // Iterate over 4 slots (each 12 bytes = 3 ints)
    do {
        // Slot structure (12 bytes):
        // offset -4: int field (written as 0)
        // offset  0: int field (written as constant)
        // offset  4: byte field (written as 0)
        // offset  5-11: padding/unused
        *(pSlot - 1) = 0;               // field at offset -4
        *pSlot = constant;               // field at offset 0
        *(char*)(pSlot + 1) = 0;         // byte at offset 4
        pSlot += 3;                      // advance by 12 bytes (3 * sizeof(int))
    } while ((int)pSlot < (int)&_DAT_011f6bec);
    
    // Set final two slots (or sentinel values) to -1
    _DAT_011f6be8 = -1;
    _DAT_011f6bec = -1;
}