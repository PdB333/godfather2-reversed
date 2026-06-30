//FUNC_NAME: ResourceManager::releaseHandle
int ResourceManager::releaseHandle(uint handle)
{
    // Handle 0xFFFFFFFF is a sentinel for "no handle" – return success (1)
    if (handle == 0xFFFFFFFF) {
        return 1;
    }

    // Bounds check: handle must be <= 0xFFF (4095) and the computed table offset must not equal a sentinel value
    // (The sentinel check is likely a safety against corrupted handles)
    if ((handle > 0xFFF) || (handle * 0x38 == 0xEE5F0D8)) { // 0xEE5F0D8 = -0x11a0f28 as unsigned
        return -1;
    }

    // The handle table is an array of pointers to ResourceControlBlock structures, each entry 0x38 bytes
    // g_handleTable is at 0x011a0f38
    ResourceControlBlock* block = *(ResourceControlBlock**)(&g_handleTable + handle * 0x38);
    if (block == nullptr) {
        return -1;
    }

    // block->refCount is at offset 0x00
    if (block->refCount != 1) {
        // Decrement reference count and return new count
        int newCount = block->refCount - 1;
        block->refCount = newCount;
        return newCount;
    }

    // refCount == 1: check state at offset 0x08
    if (block->state != 3) {
        // Not in "pending delete" state – set to 2 (likely "marked for release")
        block->refCount = 2;
        return 2;
    }

    // State is 3: actually release the resource (block->resource at offset 0x04)
    // FUN_006065a0 is a resource destructor/free function
    FUN_006065a0(block->resource, 0);
    return 0;
}