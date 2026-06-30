// FUNC_NAME: EARSObject::destructor (0x004ec000)
// Destructor for base EARS game object. Handles vtable cleanup and optional memory deallocation.
// this +0x00: vtable pointer
// this +0x20: pointer to game resource (released if non-null)

void __thiscall EARSObject::~EARSObject(void *thisObj, byte dtorFlags) {
    int *vtableAddr;
    int *deallocFuncPtr;

    // Set vtable to this class's vtable (pointer to base class?).
    *(int **)thisObj = &PTR_FUN_00e372b4;

    // Release game resource at offset 0x20 (this[8]).
    if (*(int *)((char *)thisObj + 0x20) != 0) {
        // Call vtable method at offset +4 on the resource object (likely release/delete).
        (**(code **)(*(int *)DAT_01194538 + 4))(*(int *)((char *)thisObj + 0x20), 0);
    }

    // Set vtable to base class vtable (to continue destruction chain).
    *(int **)thisObj = &PTR_LAB_00e3729c;

    // If dtorFlags bit 0 is set, deallocate this object via custom memory manager.
    if ((dtorFlags & 1) != 0) {
        // Get function pointer from allocator (FUN_009c8f80 returns pointer to allocator vtable?).
        deallocFuncPtr = (int *)FUN_009c8f80();
        // Call deallocation function (first param: this, second: unknown flag 0).
        (**(code **)(*deallocFuncPtr + 4))(thisObj, 0);
    }

    return;
}