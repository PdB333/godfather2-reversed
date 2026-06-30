// FUNC_NAME: NetObject::copyConstructor
undefined4* __fastcall NetObject::copyConstructor(int param_1) // param_1 likely source object
{
    undefined4 uVar1;
    undefined4* puVar2;
    undefined4* puVar3;
    int iVar4;
    undefined4* puVar5;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    // Get the global allocator singleton
    puVar2 = (undefined4*)FUN_009c8f80(); // returns allocator interface
    local_c = 2;   // allocation flags
    local_8 = 0x10; // alignment
    local_4 = 0;    // tag

    // Allocate memory for the new object (size 0xD0 = 208 bytes)
    puVar3 = (undefined4*)(**(code**)*puVar2)(0xd0, &local_c);
    puVar2 = (undefined4*)0x0;

    if (puVar3 != (undefined4*)0x0) {
        // Call base class constructor (pass source object)
        FUN_00473950(param_1);

        // Set vtable pointers (multiple inheritance)
        *puVar3 = &PTR_FUN_00d5f3bc;       // +0x00: first vtable
        puVar3[2] = &PTR_LAB_00d5f3b4;    // +0x08: second vtable (or pointer)

        // Generic initialization routine
        FUN_00473750();

        // Zero out fields at offsets +0x28, +0x30, +0x29
        puVar3[0x28] = 0; // +0xA0? 0x28*4 = 0xA0
        puVar3[0x30] = 0; // +0xC0? 0x30*4 = 0xC0
        puVar3[0x29] = 0; // +0xA4? 0x29*4 = 0xA4

        puVar2 = puVar3; // return the new object
    }

    uVar1 = _DAT_00d5f3b0; // global data??

    // Copy first 16 dwords from source (+0x60) to dest (+0x20) (offset 8 dwords = 32 bytes)
    puVar3 = (undefined4*)(param_1 + 0x60);
    puVar5 = puVar2 + 8;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
    }

    // Copy same source data to dest +0x60 (offset 0x18 dwords = 96 bytes)
    puVar3 = (undefined4*)(param_1 + 0x60);
    puVar5 = puVar2 + 0x18;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
    }

    // Post-copy hook with global
    FUN_00473b10(uVar1);

    return puVar2;
}