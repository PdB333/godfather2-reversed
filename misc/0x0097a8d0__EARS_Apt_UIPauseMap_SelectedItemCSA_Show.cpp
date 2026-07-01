// Xbox PDB: EARS_Apt_UIPauseMap_SelectedItemCSA_Show
// FUNC_NAME: SelectionManager::setSelection
void __thiscall SelectionManager::setSelection(int thisPtr, undefined4 *selectionData)
{
    int **ppSelectionList;
    int newSelection;
    undefined localBuffer [16]; // unused maybe?
    undefined selectionBuffer [76];

    ppSelectionList = (int **)(thisPtr + 0x104); // pointer to head of selection list
    enterCriticalSection(); // FUN_004df600 - semaphore lock

    // Check if timer is already running (bit 2 of flags at +0x60)
    if ((*(uint *)(thisPtr + 0x60) >> 2 & 1) != 0) {
        // Cancel pending timer callback FUN_00979ac0 (one-shot)
        scheduleTimer(thisPtr + 0x10, FUN_00979ac0, 1, false); // FUN_005c02f0 with param 3=1 means cancel?
        *(uint *)(thisPtr + 0x60) &= 0xfffffffb; // clear bit 2
    }

    // Check if selection is not blocked (bit 1 or 3 at +0x49 cleared)
    if ((*(byte *)(thisPtr + 0x49) & 0x0A) == 0) {
        // Copy selection data to local buffer (maybe for validation)
        copySelectionData(selectionData, selectionBuffer); // FUN_00977090
        // Log selection event? "dv_selection_csa" string
        logMessage("dv_selection_csa"); // FUN_004eacb0
        // Create new selection node in a custom linked list
        newSelection = createNode(selectionBuffer, 0xffffffff, 4, 0, 0xffffffff, 0); // FUN_004df420
        // Insert node at head of list
        if (*ppSelectionList != 0) {
            *(undefined4 *)(*ppSelectionList + 8) = 0; // clear previous next
            *ppSelectionList = 0; // detach old head? actually set head to null? 
        }
        *ppSelectionList = (int *)newSelection;
        if (newSelection != 0) {
            *(int **)(newSelection + 8) = ppSelectionList; // store address of head pointer in node
        }

        // If node was created, store selection data in object fields
        if (*ppSelectionList != 0) {
            undefined4 uVar2 = selectionData[1];
            undefined4 uVar3 = selectionData[2];
            undefined4 uVar4 = selectionData[3];
            *(undefined4 *)(thisPtr + 0x110) = *selectionData; // +0x110: selection data part 1
            *(undefined4 *)(thisPtr + 0x114) = uVar2;         // +0x114: part 2
            *(undefined4 *)(thisPtr + 0x118) = uVar3;         // +0x118: part 3
            *(undefined4 *)(thisPtr + 0x11c) = uVar4;         // +0x11c: part 4
            // Clear previous selection object at +0x120
            clearOldSelection(*(undefined4 *)(thisPtr + 0x120)); // FUN_004df830

            // Start timer if not already running (bit 2)
            if ((*(uint *)(thisPtr + 0x60) >> 2 & 1) == 0) {
                scheduleTimer(thisPtr + 0x10, FUN_00979ac0, 1, true); // FUN_005c0260 start one-shot
                *(uint *)(thisPtr + 0x60) |= 4; // set bit 2
            }
        }
    }
    return;
}