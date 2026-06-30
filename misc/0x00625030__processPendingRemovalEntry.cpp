// FUNC_NAME: processPendingRemovalEntry
// Address: 0x00625030
// Role: Called by multiple subsystems to check if an object is still valid and remove it if not.
// Entry structure: [byte flags] +0x00, [void* objectPtr] +0x04

void __fastcall processPendingRemovalEntry(byte *pendingEntry)
{
    void *objectPtr;
    bool isActive;
    
    // If the low bit of flags is clear, this entry is still pending processing
    if ((*pendingEntry & 1) == 0) {
        objectPtr = *(void **)(pendingEntry + 4); // +0x04: pointer to the object
        isActive = FUN_006250e0(objectPtr);       // Check if object is still valid/existing
        if (!isActive) {
            FUN_00624f30(objectPtr);              // Object is stale, perform removal/cleanup
        }
    }
}