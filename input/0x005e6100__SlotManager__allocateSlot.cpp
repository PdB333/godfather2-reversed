// FUNC_NAME: SlotManager::allocateSlot
// Address: 0x005e6100
// Role: Allocates and initializes a slot from a pool of 512 slots (each 0x74 bytes) managed by the class.
// The slot is identified by an index (unaff_EDI) and stores a reference (param_1) and a handle from FUN_005e5100.
// If the slot is empty, it is zeroed and initialized with default values.
// Also sets a flag at param_1+5 to 0x10 if it was zero.

int* SlotManager::allocateSlot(int param_1, int param_2, int param_3)
{
    int* slotPtr = nullptr;

    // Check if the slot array exists and index is within bounds (max 512 slots)
    if ( (*(int*)(this + 0x603c) != 0) && (unaff_EDI < 0x200) )
    {
        slotPtr = (int*)(unaff_EDI * 0x74 + *(int*)(this + 0x603c));
        if (slotPtr != nullptr)
        {
            // If slot is uninitialized (first int is zero), initialize it
            if (*slotPtr == 0)
            {
                memset(slotPtr, 0, 0x74);
                *(unsigned char*)(slotPtr + 0x16) = 0xFF;          // +0x58: byte field
                slotPtr[0x17] = 0;                                  // +0x5C: int field
                slotPtr[0x18] = DAT_00e2b1a4;                       // +0x60: int field (global)
                slotPtr[0x19] = DAT_00e2b1a4;                       // +0x64: int field (global)
                int handle = FUN_005e5100(param_3);                 // Generate handle from param_3
                slotPtr[1] = handle;                                // +0x04: store handle
                *slotPtr = param_1;                                 // +0x00: store reference
            }

            // Set a flag at param_1+5 if it is zero
            if (*(char*)(param_1 + 5) == '\0')
            {
                *(unsigned char*)(param_1 + 5) = 0x10;
            }
        }
    }

    FUN_005dbc10(); // Debug/logging call
    return slotPtr;
}