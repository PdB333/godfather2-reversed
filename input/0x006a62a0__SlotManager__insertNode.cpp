// FUNC_NAME: SlotManager::insertNode
undefined1 __thiscall SlotManager::insertNode(int this, int id, int *node, undefined4 userData1, undefined4 userData2)
{
    int iVar1;
    int *slotPtr;
    int slotIndex;
    int firstEmptySlot;
    bool bVar5;
    undefined1 result;
    int listHead;
    undefined4 nextPtr;
    
    firstEmptySlot = -1;
    result = 0;
    slotIndex = 0;
    slotPtr = (int *)(this + 0x48); // Start at slot 1 (slot 0 is at this+0x20)
    do {
        // Check four slots per iteration (slots at offsets -0x28, 0, 0x28, 0x50 from slotPtr)
        if (((firstEmptySlot < 0) || (iVar1 = slotIndex, slotPtr[-10] != 0)) &&
            (slotPtr[-10] == id)) break; // Found slot with matching id
        firstEmptySlot = iVar1;
        if ((firstEmptySlot < 0) && (*slotPtr == 0)) {
            firstEmptySlot = slotIndex + 1; // Empty slot at slotIndex+1
        }
        else if (*slotPtr == id) {
            slotIndex = slotIndex + 1;
            break;
        }
        if ((firstEmptySlot < 0) && (slotPtr[10] == 0)) {
            firstEmptySlot = slotIndex + 2;
        }
        else if (slotPtr[10] == id) {
            slotIndex = slotIndex + 2;
            break;
        }
        if ((firstEmptySlot < 0) && (slotPtr[0x14] == 0)) {
            firstEmptySlot = slotIndex + 3;
        }
        else if (slotPtr[0x14] == id) {
            slotIndex = slotIndex + 3;
            break;
        }
        slotIndex = slotIndex + 4;
        slotPtr = slotPtr + 0x28; // Move to next group of 4 slots
    } while (slotIndex < 0x20); // 32 slots total
    
    if ((slotIndex != 0x20) || (firstEmptySlot < 0)) {
        return 0; // No empty slot found and no match
    }
    
    // Allocate or reuse slot
    slotIndex = *node;
    listHead = 0;
    nextPtr = 0;
    if ((slotIndex == 0) || (slotIndex == 0x48)) {
        if (*(int *)(this + 0x678) >= 0) {
            slotPtr = (int *)(this + 0x53c + *(int *)(this + 0x678) * 0x28);
            if (&listHead == slotPtr) goto LAB_006a64a0;
            slotIndex = *slotPtr;
            bVar5 = slotIndex == 0;
            goto LAB_006a6382;
        }
        if ((*(int *)(this + 0x68c) == 0) || (*(int *)(this + 0x68c) == 0x48)) {
            FUN_006a5d20(); // Some initialization
            slotIndex = *(int *)(this + 0x68c);
            if ((slotIndex != 0) && (slotIndex != 0x48)) goto LAB_006a63c3;
        }
        else {
LAB_006a63c3:
            FUN_006a5380((int *)(this + 0x68c)); // Process another list
        }
    }
    else {
        bVar5 = (&listHead == node);
LAB_006a6382:
        if (bVar5) goto LAB_006a64a0;
        nextPtr = *(undefined4 *)(slotIndex + 4);
        *(int **)(slotIndex + 4) = &listHead;
        listHead = slotIndex;
    }
    
    slotIndex = listHead;
    if ((listHead != 0) && (listHead != 0x48)) {
        *(int *)(this + 0x520) = *(int *)(this + 0x520) + 1; // Increment count
        firstEmptySlot = this + firstEmptySlot * 0x28; // Slot base (data starts at +0x20)
        slotPtr = (int *)(firstEmptySlot + 0x24); // Pointer to list head in slot
        result = 1;
        *(int *)(firstEmptySlot + 0x20) = id; // Store id in slot
        if ((slotPtr != &listHead) && (*slotPtr != listHead)) {
            if (*slotPtr != 0) {
                FUN_004daf90(slotPtr); // Free old list
            }
            *slotPtr = listHead; // Set slot's list head to our node
            if (listHead != 0) {
                *(undefined4 *)(firstEmptySlot + 0x28) = *(undefined4 *)(listHead + 4); // Copy next pointer
                *(int **)(listHead + 4) = slotPtr; // Update node's next to point to slot's list head
            }
        }
        *(undefined4 *)(firstEmptySlot + 0x40) = userData1;
        *(undefined4 *)(firstEmptySlot + 0x44) = userData2;
        if (*(int *)(this + 0x6a4) == 0) {
            *(float *)(firstEmptySlot + 0x38) = _DAT_00d5780c; // Default scale
            *(undefined4 *)(firstEmptySlot + 0x2c) = 0;
            *(undefined4 *)(firstEmptySlot + 0x30) = 0;
            *(undefined4 *)(firstEmptySlot + 0x34) = 0;
        }
        else {
            *(undefined8 *)(firstEmptySlot + 0x2c) = *(undefined8 *)(this + 0x6a8); // Copy vector
            *(undefined4 *)(firstEmptySlot + 0x34) = *(undefined4 *)(this + 0x6b0);
            *(float *)(firstEmptySlot + 0x38) = _DAT_00d5780c / (*(float *)(this + 0x6b4) * *(float *)(this + 0x6b4));
        }
        FUN_006a57c0(); // Post-insert callback
    }
LAB_006a64a0:
    if (*(int *)(this + 0x6b8) == 0) {
        *(undefined4 *)(this + 0x6a4) = 0;
    }
    else if (*(int *)(this + 0x6b8) == 1) {
        *(undefined4 *)(this + 0x6b8) = 2;
    }
    if (listHead != 0) {
        FUN_004daf90(&listHead); // Clean up local list head
    }
    return result;
}