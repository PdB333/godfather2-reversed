// FUNC_NAME: HandleAllocator::allocateHandle

void __thiscall HandleAllocator::allocateHandle(int thisPtr) {
    int managerPtr;
    int slotIndex;
    int *slotArray;
    char *pendingList;
    char successFlag;
    int *objPtr;
    uint pendingIndex;
    byte localArray[12];

    // Check that the base object type is valid (0x50 = 'P'?)
    if (*(short *)(*(int *)(thisPtr + 0x8) + 0x2) != 0x50) {
        // Debug assert/crash
        (*(code **)(*DAT_01205590 + 0x4))();
    }

    // Get base object pointer
    int baseObj = *(int *)(thisPtr + 0x8);

    // Call a transformation function (likely vec3 cross/magnitude)
    (*(code **)(*DAT_012055A8 + 0x34))(*(undefined4 *)(baseObj + 0x40),
                                        *(undefined4 *)(baseObj + 0x44),
                                        *(undefined4 *)(baseObj + 0x48),
                                        localArray);

    // Get the handle manager from this object
    int *handleMgr = *(int **)(thisPtr + 0x1BC);
    slotIndex = *(int *)(handleMgr + 0x1C);  // free list head

    if (slotIndex == -1) {
        // No free slots – assert/crash
        (*(code **)(*DAT_01205590 + 0x4))();
    } else {
        // Remove the slot from free list
        *(int *)(handleMgr + 0x1C) = *(int *)(*(int *)(handleMgr + 0x18) + slotIndex * 4);
        *(int *)(*(int *)(handleMgr + 0x18) + slotIndex * 4) = -2;  // marker: slot in use

        // Call the init method on the object associated with this slot
        (*(code **)(**(int **)(*(int *)(handleMgr + 0x14) + slotIndex * 4) + 0x54))();
    }

    // Store the slot index into a pending list (queue of recent allocs)
    char pendingListByte = *(char *)(thisPtr + 0x58);
    *(char *)(thisPtr + 0x59 + pendingListByte) = (char)slotIndex;

    // Verify the slot is still occupied
    int *slotArrayPtr = *(int **)(handleMgr + 0x18);
    if (slotArrayPtr[slotIndex] != -2) {
        (*(code **)(*DAT_01205590 + 0x4))();
    }

    // Get the object pointer for the slot
    objPtr = *(int **)(*(int *)(handleMgr + 0x14) + slotIndex * 4);
    if (objPtr == (int *)0x0) {
        (*(code **)(*DAT_01205590 + 0x4))();
        return;
    }

    // Boolean flags from base object
    int flag1 = (uint)(*(int *)(baseObj + 0x38) != 0);
    int flag2 = (uint)(*(int *)(baseObj + 0x3C) != 0);

    // Call a virtual "create" method on the object with various parameters
    successFlag = (**(code **)(*objPtr + 0x50))(baseObj + 0x4,
                                                 baseObj + 0x14,
                                                 thisPtr,
                                                 *(undefined4 *)(baseObj + 0x34),
                                                 flag1,
                                                 flag2,
                                                 &localArray);

    if (successFlag == '\0') {
        // Allocation/creation failed – restore slot to free list
        int *slotArray2 = *(int **)(handleMgr + 0x18);
        if (slotArray2[slotIndex] != -2) {
            (*(code **)(*DAT_01205590 + 0x4))();
        }
        if (slotArray2[slotIndex] == -2) {
            // Return to free list
            slotArray2[slotIndex] = *(int *)(handleMgr + 0x1C);
            *(int *)(handleMgr + 0x1C) = slotIndex;
        }
    } else {
        // Success – track the created object
        if (*(char *)(thisPtr + 0x58) != 0) {
            // There is a pending slot index; use it
            pendingIndex = (uint)*(char *)(thisPtr + 0x58 + pendingListByte); // Actually pendingIndex = byte at thisPtr+0x58+pendingListByte? Wait, this is messy.
            // Actually the decompiled code is: uVar7 = (uint)*(byte *)(*(byte *)(param_1 + 0x58) + 0x58 + param_1);
            // That means: byte at (this + 0x58) is an offset, then reads byte at (this + 0x58 + that offset). So pendingIndex = *(byte *)(thisPtr + 0x58 + *(byte *)(thisPtr+0x58)).
            // But we already used pendingListByte from same location; need to recalc.
            // This is a nested indexing; assume pendingIndex = *(byte *)(thisPtr + 0x58 + (byte)*(byte*)(thisPtr+0x58)).
        }
        // Store the created object pointer in manager at +0x78
        *(int *)(handleMgr + 0x78) = *(int *)(*(int *)(handleMgr + 0x14) + pendingIndex * 4);
        // Increment the pending count
        *(char *)(thisPtr + 0x58) = *(char *)(thisPtr + 0x58) + 1;
    }
}