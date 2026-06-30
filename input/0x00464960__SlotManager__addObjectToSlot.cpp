// FUNC_NAME: SlotManager::addObjectToSlot
int __thiscall SlotManager::addObjectToSlot(int thisPtr, byte slotIndex, int objectHandle, undefined4 context)
{
    // Check if object handle is null
    if (objectHandle == 0) {
        return 0;
    }

    // Resolve object handle to actual pointer (e.g., from handle table)
    int resolvedObjectPtr = resolveObjectHandle(objectHandle); // FUN_004dafd0

    // Find index in global manager's object array
    int index = findObjectInGlobalList(&resolvedObjectPtr); // FUN_00466b00

    if (index >= 0) {
        // Global manager pointer (DAT_01205400)
        int* globalManager = g_globalManager;
        // Calculate pointer to object entry in global manager's list (offset 4 + index * 8)
        int* objectEntry = (int*)(*globalManager + 4 + index * 8);
        if (objectEntry != (int*)0x0) {
            int objectPtr = *objectEntry; // +0x00: pointer to object? or object itself

            // Increment reference count at offset +8 of the object
            char* refCount = (char*)(objectPtr + 8);
            *refCount = *refCount + 1;

            // Callback: reference added
            onReferenceAdded(); // FUN_00465310

            // Calculate slot base address (slot size 0x168)
            int slotBase = (uint)slotIndex * 0x168 + thisPtr;

            // Current count in slot at offset +0x10
            int count = *(int*)(slotBase + 0x10);
            // Store object pointer into array at offset +0x14
            *(int*)(slotBase + 0x14 + count * 4) = objectPtr;
            // Increment count
            *(int*)(slotBase + 0x10) = count + 1;

            // Callback: slot data modified
            onSlotModified(); // FUN_004cdf80

            // Final callback with context
            onContextCallback(context); // FUN_00464210

            return 1;
        }
    }
    return 0;
}