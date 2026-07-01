// FUNC_NAME: ObjectPool::allocateNode
// Address: 0x0094cc00
// Reconstructed from Ghidra decompilation
// This function allocates a node from a free list, builds a control word from parameters,
// and constructs an object via a callback. Likely part of a memory pool or entity allocator.

unsigned int __thiscall ObjectPool::allocateNode(
    int this,
    unsigned int allocType,          // param_2
    int nodeSize,                    // param_3
    unsigned int param4,             // param_4
    int* outHandle,                  // param_5 - output handle (written to)
    int category1,                   // param_6 - 1,2 or 3 -> bits 0,1,2
    int flag1,                       // param_7 - 1 -> bit3 (0x8)
    int flag2,                       // param_8 - 1->bit5 (0x20), 2->bit4 (0x10)
    int flag3,                       // param_9 - 1 -> bit6 (0x40)
    int flag4,                       // param_10 - 0->bit9 (0x200), 1->bit8 (0x100)
    unsigned int extra1,             // param_11
    unsigned int extra2,             // param_12
    unsigned int extra3,             // param_13
    unsigned int extra4              // param_14
)
{
    unsigned int* pSlot;        // puVar2 - pointer to slot where result is stored
    unsigned int* freeNode;     // puVar1 - current free list head
    unsigned int result;        // uVar3 - return value from constructObject
    unsigned int flags;         // uVar4 - combined flag word

    result = 0;
    if (nodeSize != 0) {
        // Resolve the output handle (prepare for potential allocation)
        *outHandle = resolveHandle(*outHandle);

        flags = 0;

        // Build flag word from parameters
        if (flag1 == 1) {
            flags = 8;              // bit3
        }
        if (flag2 == 1) {
            flags |= 0x20;          // bit5
        }
        else if (flag2 == 2) {
            flags |= 0x10;          // bit4
        }
        if (category1 == 1) {
            flags |= 1;             // bit0
        }
        else if (category1 == 2) {
            flags |= 2;             // bit1
        }
        else if (category1 == 3) {
            flags |= 4;             // bit2
        }
        if (flag3 == 1) {
            flags |= 0x40;          // bit6
        }
        if (flag4 == 0) {
            flags |= 0x200;         // bit9
        }
        else if (flag4 == 1) {
            flags |= 0x100;         // bit8
        }

        // Global debug flag check (DAT_0112af90+0x48)
        // If debug is disabled, force debug bit and log
        if (*(unsigned char*)(0x0112af90 + 0x48) == '\0') {
            flags |= 0x80;          // bit7 = debug flag
            logDebugMessage(&DAT_011301a8);  // FUN_00408680 - likely debug output
        }

        // Get pointer to the slot where the allocation result will be stored
        pSlot = (unsigned int*)getSlotPointer(outHandle);

        // Check if free list is empty and pool is not expandable -> trigger error
        if ( (*(int*)(this + 0x5c) == 0) &&
             ( (*(int*)(this + 0x58) == 0) || ((*(unsigned char*)(this + 0x4c) & 1) == 0) )) {
            onAllocationError();  // FUN_004de190 - assert / error handler
        }

        // Pop a node from the free list (single linked list)
        freeNode = *(unsigned int**)(this + 0x5c);  // +0x5c: head of free list
        if (freeNode != nullptr) {
            result = *freeNode;                            // next pointer becomes new head
            *(int*)(this + 0x38) = *(int*)(this + 0x38) + 1;  // +0x38: allocation counter
            *(int*)(this + 0x34) = *(int*)(this + 0x34) - 1;  // +0x34: free counter
            *(unsigned int*)(this + 0x5c) = result;            // update free list head

            if (freeNode != nullptr) { // redundant check, but preserved from original
                // Construct the object in the allocated node using the built flags
                result = constructObject(*outHandle, allocType, nodeSize, param4,
                                         flags, extra1, extra2, extra3, extra4);
                *pSlot = result;
                return *outHandle;
            }
        }

        // No free nodes available: set slot to 0 and return handle unchanged
        *pSlot = 0;
        result = *outHandle;
    }
    return result;
}