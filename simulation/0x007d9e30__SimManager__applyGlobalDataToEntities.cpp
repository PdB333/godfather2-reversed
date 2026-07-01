// FUNC_NAME: SimManager::applyGlobalDataToEntities
void __fastcall SimManager::applyGlobalDataToEntities(int thisPtr)
{
    // Call a virtual method (likely pre-update or initialization hook)
    (**(code **)(**(int **)(thisPtr + 0x58) + 0x308))();

    // Set bit 2 of the flags field at +0xC4 (0x04)
    *(uint *)(thisPtr + 0xC4) = *(uint *)(thisPtr + 0xC4) | 4;

    // Get a linked list of all managed objects from the global manager singleton (type 2)
    // The returned structure has a head pointer at offset 0
    undefined4 *listHeadPtr = FUN_0043c2c0(2);
    int globalValue = DAT_00e446f0; // Global value to apply

    // Traverse the linked list: each node has object pointer at offset 0, next at offset 4
    for (int *node = (int *)*listHeadPtr; node != (int *)0x0; node = (int *)node[1])
    {
        int objectPtr = *node; // The actual object (e.g., Entity)
        // Check if a sub-object pointer at +0x130 exists
        if (*(int *)(objectPtr + 0x130) != 0)
        {
            // Set field at +0x30 of that sub-object to the global value
            *(undefined4 *)(*(int *)(objectPtr + 0x130) + 0x30) = globalValue;
        }
    }
    return;
}