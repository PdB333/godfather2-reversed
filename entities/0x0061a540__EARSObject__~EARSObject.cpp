// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::~EARSObject(void)
{
    // Free pointer at offset +0x20 (likely a dynamically allocated sub-object)
    if (*(int *)(this + 0x20) != 0) {
        freeMemory(*(int *)(this + 0x20));  // FUN_009c8f10 – custom deallocation
    }

    // Set vtable pointer at +0x14 to the static vtable for this class (PTR_LAB_00e40f38)
    if (this != 0) {
        *(undefined4 **)(this + 0x14) = &PTR_LAB_00e40f38;
    } else {
        // Safe guard: if this is null, avoid write – but original code would crash
        // Probably a decompiler artifact; the actual code likely checked this before.
    }

    // Clear global flag (e.g., an active-instance counter)
    _DAT_01223558 = 0;

    // Call base class destructors / cleanup routines
    baseDestructor1();  // FUN_004083d0
    baseDestructor2();  // FUN_0049c640

    return;
}