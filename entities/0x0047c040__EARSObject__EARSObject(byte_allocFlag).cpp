// FUNC_NAME: EARSObject::EARSObject(byte allocFlag)
void* __thiscall EARSObject::EARSObject(void* this, byte allocFlag) {
    // Set main vtable pointer
    *(int**)this = &PTR_FUN_00e3314c;  // Main vtable

    // Set additional interface vtable pointers for multiple inheritance
    // Offsets: 0x3C = 0xF * 4, 0x48 = 0x12 * 4
    *(int**)((char*)this + 0x3C) = &PTR_LAB_00e33168;  // Interface vtable 1
    *(int**)((char*)this + 0x48) = &PTR_LAB_00e33178;  // Interface vtable 2

    // Construct base subobject at offset 0x50 (this + 0x14 * 4)
    // Sequence of two constructor calls for this base
    constructBasePart1((void*)((char*)this + 0x50));
    constructBasePart2((void*)((char*)this + 0x50));

    // Global engine initialization
    initGlobalSystems();

    // If this object was heap-allocated (flag bit 0 set), notify allocator
    if (allocFlag & 1) {
        // Global structure at DAT_01223410, offset 0x2D4 contains a vtable pointer
        // Index 1 (offset 4) is the allocated notification callback
        typedef void (*AllocCallback)(void*, int);
        AllocCallback notifyAlloc = *(AllocCallback*)(*(int**)(DAT_01223410 + 0x2D4) + 4);
        notifyAlloc(this, 0);
    }

    return (void*)this;
}