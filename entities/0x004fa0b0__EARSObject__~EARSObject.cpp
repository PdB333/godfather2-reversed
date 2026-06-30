// FUNC_NAME: EARSObject::~EARSObject
void __thiscall EARSObject::destructor(void)
{
    int* iVar1;
    void* pvVar2;
    int* piVar3;

    // Set vtable to base destructing vtable (first base)
    *(void**)this = &PTR_FUN_00e37a58;

    // Perform base cleanup (called twice)
    FUN_004ebba0();
    FUN_004ebba0();

    // Handle weak reference at offset +0x16c
    iVar1 = *(int**)((int)this + 0x16c);
    if (iVar1 != 0) {
        // Set a flag in the weak reference object at +0xc
        *(uint32_t*)(iVar1 + 0xc) |= 0x200000;
        FUN_0051d6b0();
        // Clear weak pointer: double indirection at +8
        if (*(void***)(iVar1 + 8) != (void**)0x0) {
            **(void***)(iVar1 + 8) = 0;
            *(void**)(iVar1 + 8) = 0;
        }
    }

    // Handle buffer at offset +0x40
    pvVar2 = *(void**)((int)this + 0x40);
    if (pvVar2 != 0) {
        FUN_004fc520();
        // Log the freed pointer in the global free list
        piVar3 = (int*)(DAT_01206880 + 0x14);
        **(void***)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
        *piVar3 += 4;
        *(void*)*piVar3 = pvVar2;
        *piVar3 += 4;
        *(void**)((int)this + 0x40) = 0;
        *(int*)((int)this + 0x44) = 0;
    }

    // Set vtable to second base destructing vtable
    *(void**)this = &PTR_FUN_00e37110;

    // Handle child object at offset +0x10
    iVar1 = *(int**)((int)this + 0x10);
    if (iVar1 != 0) {
        // Log this pointer in the global free list
        piVar3 = (int*)(DAT_01206880 + 0x14);
        **(void***)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
        *piVar3 += 4;
        *(int*)*piVar3 = iVar1;
        *piVar3 += 4;
        *(int*)((int)this + 0x10) = 0;
        *(int*)((int)this + 0x14) = 0;
    }

    return;
}