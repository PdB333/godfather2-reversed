// FUNC_NAME: RefCountedObjectManager::releaseWeakHandle

void __thiscall RefCountedObjectManager::releaseWeakHandle(int param_1, int param_2)
{
    // +0x4e0: flag indicating if deletion/cleanup should occur (e.g., debug or enable flag)
    // Possibly "m_bEnableCleanup" or similar
    if (*(int*)(param_1 + 0x4e0) != 0) {
        // FUN_0085bb90 likely performs final cleanup/deletion of the underlying object
        FUN_0085bb90(param_2);
    }

    // param_2 points to a Handle structure:
    // +0x04: pointer to RefCountedObject (m_pObject)
    // The RefCountedObject itself has layout:
    // +0x00: vtable pointer
    // +0x04: short strongRefCount or deleteFlag
    // +0x06: short weakRefCount (ref count for this handle type)
    // +0x08: pointer to actual data (or self)
    int* pObject = *(int**)(param_2 + 4);  // Get pointer to RefCountedObject
    undefined4** ppRefCountData = *(undefined4***)(pObject + 8);  // Get pointer to ref count data (puVar1)

    // If weakRefCount is 1, clear the handle's object pointer to prevent dangling
    if (*(short*)((int)ppRefCountData + 6) == 1) {
        *(undefined4*)(pObject + 8) = 0;  // Clear the pointer in the handle?
    }

    // If strongRefCount (at ppRefCountData+1 byte offset = +4) is non-zero,
    // decrement weakRefCount (at +6). If weakRefCount becomes zero, call destructor.
    if (*(short*)(ppRefCountData + 1) != 0) {  // Short at offset 4 from ppRefCountData
        *(short*)((int)ppRefCountData + 6) = *(short*)((int)ppRefCountData + 6) - 1;
        if (*(short*)((int)ppRefCountData + 6) == 0) {
            // Call the first virtual function (assumed destructor) with argument 1
            (**(code**)*ppRefCountData)(1);
        }
    }

    FUN_00540410(); // Pop profiling scope marker?
    return;
}