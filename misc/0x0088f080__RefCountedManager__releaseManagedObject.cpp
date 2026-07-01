// FUNC_NAME: RefCountedManager::releaseManagedObject
void __thiscall RefCountedManager::releaseManagedObject(int thisPtr, int* outRefCount, int handle) {
    // Increment? Actually decrement count at this+0x14 (likely reference count of manager itself)
    *(int*)(thisPtr + 0x14) = *(int*)(thisPtr + 0x14) - 1; // manager ref count decremented

    // Call: get current reference count of the managed object (handle)
    int refCount = getObjectRefCount(handle); // FUN_00ab3c50

    // Call: cleanup internal buffer at this+0x4 (maybe raw buffer pointer)
    cleanupObjectBuffer(handle, (void*)(thisPtr + 4)); // FUN_00ab4010

    // Call: destroy or release the object handle
    destroyObjectHandle(handle); // FUN_009c8f10

    // Store the old reference count for caller
    *outRefCount = refCount;
}

// Assumed callee signatures (not exported, for documentation only)
int getObjectRefCount(int handle);
void cleanupObjectBuffer(int handle, void* buffer);
void destroyObjectHandle(int handle);