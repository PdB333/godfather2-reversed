// FUNC_NAME: GhostConnection::resolveGhostFromSlot
// Address: 0x005fcde0
// Role: Resolves a ghost object from a slot index, using internal arrays and transformed indexing.

int __fastcall GhostConnection::resolveGhostFromSlot(int this, int slotIndex)
{
    short capacity = *(short *)(this + 0x90);   // +0x90: capacity or sequence count
    short baseVal  = *(short *)(this + 0x3c);   // +0x3c: base offset or window start
    ushort transformedIndex = (capacity - baseVal) + (short)slotIndex;

    int result = 0;
    if (transformedIndex != 0xFFFF) // invalid index sentinel
    {
        // Array of 8-byte slot descriptors at +0x38
        int* slotArray = *(int **)(this + 0x38);
        // Check if the first 4 bytes of the slot for this index are zero (empty/unused)
        if (slotArray[slotIndex * 2] == 0) // each slot is 8 bytes, so offset = slotIndex*2*4 = slotIndex*8
        {
            // Array of ghost object pointers at +0x8c
            int** ghostPtrArray = *(int ***)(this + 0x8c);
            int ghostPtr = (int)ghostPtrArray[transformedIndex]; // get the pointer for the transformed index
            result = FUN_005fafc0(ghostPtr); // likely allocate or retrieve ghost object
            if (result != 0)
            {
                FUN_005fa490(result); // likely initialize the ghost object
            }
        }
    }
    return result;
}