// FUNC_NAME: EARSObject::~EARSObject

void __thiscall EARSObject::~EARSObject(void)
{
    undefined4 *puVar1;
    // unaff_ESI is 'this' — the object being destroyed
    undefined4 *thisPtr = reinterpret_cast<undefined4 *>(this);

    puVar1 = thisPtr + 2;                               // +0x8 (third vtable slot)

    // Set vtables to the derived class's vtable pointers (first call from destructor chain)
    thisPtr[0] = &PTR_LAB_00e3926c;                     // +0x0: first base vtable
    thisPtr[1] = &PTR_LAB_00e39280;                     // +0x4: second base vtable
    *puVar1   = &PTR_LAB_00e39294;                      // +0x8: third base vtable

    // +0x10: pointer to dynamically allocated resource; if non‑null, release it
    if (thisPtr[4] != 0) {
        FUN_009f1b20(thisPtr);                          // release first base resources
        FUN_009f1ad0(puVar1);                           // release second base resources
        FUN_009f01a0();                                 // global cleanup (e.g., memory manager)
        thisPtr[4] = 0;                                 // clear resource pointer
    }

    // Restore vtable pointers to base class versions (pure virtual for the first)
    *puVar1   = &PTR_LAB_00e39260;                      // +0x8: third base (base vtable)
    thisPtr[1] = &PTR_LAB_00dc3dd4;                     // +0x4: second base (base vtable)
    thisPtr[0] = &PTR___purecall_00e3924c;              // +0x0: first base → purecall (abstract)

    return;
}