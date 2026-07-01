// FUNC_NAME: Monopoly::updateSelection
void __thiscall Monopoly::updateSelection(int *thisPtr, void *selectionData, byte selectionSource)
{
    // thisPtr is a Monopoly*; cast to struct for offset access
    // Offsets (in bytes from thisPtr):
    //   +0x12: byte selectionActive
    //   +0x17: int  selectionCount
    //   +0x23: int  currentSelectionIndex   (0x8C)
    //   +0x30: int  currentItemID           (0xC0)
    //   +0x31: byte selectionChanged        (0xC4)
    // vtable +0x9C: virtual update() returns something

    int *dataInt = (int *)selectionData;
    int tmp;

    if (selectionData == nullptr) {
        // No selection data: clear state
        thisPtr[0x30] = -1;                              // currentItemID = -1
        thisPtr[0x23] = (thisPtr[0x17] != 0) - 1;        // currentSelectionIndex = (selectionCount>0 ? 0 : -1)
    } else {
        // Process incoming selection structure
        int **ppDataBlock = (int **)(dataInt + 0x30);     // offset 0xC0 in bytes = (0xC0/4)=0x30 ints
        if (*ppDataBlock != nullptr) {
            beginUpdate();                                // FUN_0095bc80()
            int firstID = **(int **)ppDataBlock;          // *(*ppDataBlock) – first element of data block
            tmp = resolveID(&firstID);                    // FUN_00486770: get canonical index
            if (tmp < 0) tmp = -1;
            thisPtr[0x23] = tmp;                         // currentSelectionIndex = resolved index

            endUpdate();                                  // FUN_0095bd70()

            int rawID = *(int *)(dataInt + 0x0E);         // offset 0x38 in bytes = (0x38/4)=14 (0xE) ints
            tmp = resolveID(&rawID);
            if (tmp < 0) tmp = -1;
            thisPtr[0x30] = tmp;                         // currentItemID = resolved ID

            // Debug logging
            debugPrint("UpdateMonopolySelection", 0, &DAT_00d8ca78, 0); // FUN_005a04a0

            // If a valid selection exists and selectionActive is set, activate the selection
            if ((thisPtr[0x23] != -1) && (*(char *)(thisPtr + 0x12 / 4 + 1) != 0)) {
                activateSelection(thisPtr[0x23], 0);     // FUN_00956a50
            }

            // Mark the source of this update
            *(byte *)(thisPtr + 0xC4 / 4 + 1) = selectionSource; // offset 0x31 in int indexing = 0xC4/4=0x31? careful: thisPtr is int* so +1 = 4 bytes, but we need byte. Use byte cast.
        }
    }

    // Call virtual update() and pass its return value to finalizeUpdate
    int vtable = *(int *)thisPtr;
    int updateResult = (*(int (__thiscall **)(int *))(vtable + 0x9C))(thisPtr);
    finalizeUpdate(updateResult);                        // FUN_0097b8e0
}