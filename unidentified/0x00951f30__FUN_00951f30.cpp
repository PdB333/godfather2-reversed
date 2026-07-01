// FUNC_NAME: SomeClass::removeAndCleanupSelection
void __fastcall SomeClass::removeAndCleanupSelection(int thisPtr)
{
    int selectedIndex;
    int currentItem;
    int iVar1;
    char cVar2;
    int iVar3;
    uint numSlots;
    int local_14;
    int local_8;
    uint slotIndex;

    // +0xa0: current selection index, -1 means none
    if (*(int *)(thisPtr + 0xa0) == -1) {
        selectedIndex = -1;
    }
    else {
        // +0x64 (100): pointer to array of items
        // +0xa0: index into that array
        selectedIndex = *(int *)(*(int *)(thisPtr + 100) + *(int *)(thisPtr + 0xa0) * 4);
    }
    *(int *)(thisPtr + 0xa0) = -1; // clear selection
    // +0x68: count of items
    *(int *)(thisPtr + 0x68) = 0;
    // Free the item array
    FUN_009c8f10(*(int *)(thisPtr + 100));
    *(int *)(thisPtr + 100) = 0;
    *(int *)(thisPtr + 0x6c) = 0; // +0x6c: some other count

    // +0x78: some index, -1 means none
    if (*(int *)(thisPtr + 0x78) != -1) {
        // DAT_0112a558 + 0x38: number of active entities/objects
        numSlots = *(uint *)(DAT_0112a558 + 0x38);
        // +0x58: pointer to array of something
        currentItem = *(int *)(*(int *)(thisPtr + 0x58) + *(int *)(thisPtr + 0x78) * 4);
        if (numSlots != 0) {
            for (slotIndex = 0; slotIndex < numSlots; slotIndex++) {
                iVar1 = FUN_006b0770(slotIndex); // get object by slot index
                if (((iVar1 != 0) && 
                     (cVar2 = FUN_006b4440(), cVar2 != '\0')) && // some validity check
                    (cVar2 = FUN_00849ea0(*(int *)(iVar1 + 0x48)), cVar2 != '\0')) && // check type
                   (*(int *)(iVar1 + 0xc4) == currentItem)) { // match item ID
                    iVar3 = *(int *)(iVar1 + 0x38); // get some ID from object
                    local_8 = iVar3;
                    FUN_004866e0(&local_8); // process/remove this ID
                    if (selectedIndex == iVar3) {
                        // Restore selection index if we removed the previously selected item
                        *(int *)(thisPtr + 0xa0) = *(int *)(thisPtr + 0x68) - 1;
                    }
                }
            }
        }
    }
    // Ensure selection index is valid
    if ((*(uint *)(thisPtr + 0x68) != 0) &&
       ((*(uint *)(thisPtr + 0x68) <= *(uint *)(thisPtr + 0xa0) ||
        (*(uint *)(thisPtr + 0xa0) == 0xffffffff)))) {
        *(int *)(thisPtr + 0xa0) = 0;
    }
}