// FUNC_NAME: DeletionManager::processDeletions
void __fastcall DeletionManager::processDeletions(DeletionManager* thisPtr)
{
    // Loop over entries in the pending deletion array (offset +0xB4 = array of pointers, +0xB8 = count)
    uint entryIndex = 0;
    if (thisPtr->pendingDeletionCount != 0) {
        do {
            // Retrieve the entry pointer from the array
            void* entryPtr = *(void**)(thisPtr->pendingDeletionArray + entryIndex * 4);
            // Set thread context (likely a mutex or TLS set)
            FUN_00790110(0);
            // Process the manager's state before deletion (maybe lock or update counters)
            FUN_00791350(thisPtr);
            // Check if deletion is allowed (e.g., object is ready to be freed, not in use)
            bool deletionAllowed = FUN_00791230();
            if (deletionAllowed) {
                // Perform the actual deletion/finalization of the entry
                FUN_00792d80(entryPtr);
            }
            entryIndex++;
        } while (entryIndex < thisPtr->pendingDeletionCount);
    }

    // Clear the pending deletion list
    thisPtr->pendingDeletionCount = 0;
    // Free the array memory (likely custom deallocation)
    FUN_009c8f10(thisPtr->pendingDeletionArray);
    thisPtr->pendingDeletionArray = 0;
    // Reset capacity field
    thisPtr->pendingDeletionCapacity = 0;

    // Run additional cleanup for other lists
    FUN_006b2f70();

    // Check if all related lists are empty (offsets +0x88, +0xA0, +0xAC, +0xB8)
    if (thisPtr->otherList1 == 0 && thisPtr->otherList2 == 0 &&
        thisPtr->otherList3 == 0 && thisPtr->pendingDeletionCount == 0) {
        // If completely empty, release global reference (e.g., reference counted manager)
        FUN_004086d0(&DAT_0112a640);  // Release/DecRef
        return;
    }
    // Otherwise, add a reference (or mark as still active)
    FUN_00408680(&DAT_0112a640);  // AddRef/IncRef
}