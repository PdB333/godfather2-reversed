// FUNC_NAME: EARSObject::destroy
void __thiscall EARSObject::destroy(void) {
    // Switch vtable to cleanup state
    *(void**)this = (void*)s_dyingVTable; // +0x00

    // Check if this object is in use: flags bit 1 (byte at +0x2C) and handle non-zero and active flag false
    if (((*(unsigned char*)((int)this + 0x2C) & 2) != 0) && 
        (*(unsigned int*)((int)this + 0x30) != 0) && 
        (*(char*)((int)this + 0x35) == '\0')) {
        // Perform additional cleanup (e.g., unregister from manager)
        unregisterFromManager();
    }

    unsigned int handleValue = *(unsigned int*)((int)this + 0x30); // handle at +0x30
    if ((handleValue != 0) && ((handleValue & 0xFFFF) < 0x200)) {
        int* tableEntry = (int*)((handleValue & 0xFFFF) * 0x30 + 0x10 + g_handleTableBase); // DAT_012234bc
        if ((tableEntry != 0) && (*(unsigned int*)(tableEntry + 0x2C) == handleValue) && (tableEntry != 0)) {
            // Clear handle table entry fields
            *(int*)(tableEntry + 0x24) = 0;
            *(int*)(tableEntry + 0x28) = 0;
        }
    }

    // Switch vtable to dead state
    *(void**)this = (void*)s_deadVTable; // +0x00

    int* nextFree = *(int**)((int)this + 0x10); // next free pointer at +0x10
    if (nextFree != 0) {
        int** poolHead = (int**)(g_poolManager + 0x14); // DAT_01206880
        // Insert object into pool free list
        **(void***)(g_poolManager + 0x14) = (void*)s_freeListVTable;
        *poolHead = (int*)((int)*poolHead + 4);
        **(int**)(*poolHead) = (int)nextFree;
        *poolHead = (int*)((int)*poolHead + 4);
        // Clear the object's pool list pointers
        *(int*)((int)this + 0x10) = 0;
        *(int*)((int)this + 0x14) = 0;
    }

    // Destructor complete
    return;
}