// FUNC_NAME: SimObject::SimObject
void __thiscall SimObject::SimObject(SimObject *this)
{
    // Setup vtable pointers for multiple inheritance layers (offsets in bytes)
    *(void**)this = &SimObject_vtable;                          // +0x00: primary vtable
    *(void**)((char*)this + 0x3C) = &SimObject_Interface1_vtbl; // +0x3C: interface vtable
    *(void**)((char*)this + 0x48) = &SimObject_Interface2_vtbl; // +0x48: another interface
    *(void**)((char*)this + 0x50) = &SimObject_Interface3_vtbl; // +0x50: third interface

    // Clean up any residual dynamically allocated members (pooled construction)
    // offset 0x98 = 0x26 * 4, offset 0x90 = 0x24 * 4
    if (*(void**)((char*)this + 0x98) != 0) {
        releaseRefCountedObject((void**)((char*)this + 0x98));   // FUN_004daf90
    }
    if (*(void**)((char*)this + 0x90) != 0) {
        releaseRefCountedObject((void**)((char*)this + 0x90));   // FUN_004daf90
    }

    // Call base class initialization (likely sets default values or registers with manager)
    simObjectBaseInit();                                         // FUN_00473880
}