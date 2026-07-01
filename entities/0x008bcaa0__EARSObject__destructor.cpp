// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(void* this) {
    // Set vtable to a specific destructor vtable (stage 1)
    *(void**)this = &PTR_FUN_00d7bc58;
    // Set secondary vtable (likely interface or destructor chain)
    *(void**)((char*)this + 4) = &PTR_LAB_00d7bc54;

    // Notify the engine with a unique object identifier (0x253131b5)
    FUN_004639e0(0x253131b5);

    // If the member pointer at offset 8 is non-null, destroy it
    if (*(void**)((char*)this + 8) != 0) {
        FUN_009c8f10(*(void**)((char*)this + 8));
    }

    // Transition to final destructor vtable (stage 2)
    *(void**)((char*)this + 4) = &PTR_LAB_00d7bc50;
    // Clear a global reference count or state
    DAT_01129908 = 0;
    // Set the primary vtable to a stub/end-of-life vtable
    *(void**)this = &PTR_LAB_00e30fe0;
}