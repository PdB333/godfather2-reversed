// FUNC_NAME: NetObjectScopeManager::removeFromScopeList
void __thiscall NetObjectScopeManager::removeFromScopeList(NetObjectScopeManager* this, DynamicArray* array, NetObject* objectToRemove)
{
    uint index;
    int* pData;

    // Search for the object pointer in the array
    index = 0;
    if (array->count != 0) {
        pData = array->data;
        while (*pData != (int)objectToRemove) {
            index++;
            pData++;
            if ((uint)array->count <= index) {
                // Not found
                return;
            }
        }
        // Found at index
        if ((int)index >= 0) {
            // Clear bit 27 (0x08000000) in the object's flags at offset 0x5C
            *(uint*)((int)objectToRemove + 0x5C) &= 0xF7FFFFFF; // ~0x08000000

            // Remove the element by swapping with the last element
            if (index != (uint)(array->count - 1)) {
                *(int*)(array->data + index) = *(int*)(array->data + array->count - 1);
            }
            array->count--;

            // Set up a temporary context for scope locking (critical section)
            ScopeLockContext context;
            context.vtable = &g_ScopeLockVTable;  // PTR_LAB_00d5dbb0
            context.data = g_SomeData;            // DAT_0112a5a4
            context.flag = 0;
            context.thisPtr = this;               // local_10 = param_1

            // Acquire scope lock (likely via a static mutex)
            AcquireScopeLock(&context, 0);        // FUN_00408a00

            // Check if all children/sub-objects are null (offsets +0x88, +0xA0, +0xAC, +0xB8)
            if ((*(int*)(this + 0x88) == 0) &&
                (*(int*)(this + 0xA0) == 0) &&
                (*(int*)(this + 0xAC) == 0) &&
                (*(int*)(this + 0xB8) == 0)) {
                // No remaining references – finalize removal
                FinalizeRemoval(&g_GlobalLock);   // FUN_004086d0
            } else {
                // Still referenced – update state
                UpdateRemainingReferences(&g_GlobalLock); // FUN_00408680
            }
        }
    }
    return;
}