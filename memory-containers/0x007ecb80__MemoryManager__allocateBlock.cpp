// FUNC_NAME: MemoryManager::allocateBlock
undefined4* __thiscall MemoryManager::allocateBlock(undefined4* this, undefined4 param_2)
{
    undefined4* puVar1;
    undefined4 unaff_retaddr; // return address from caller
    undefined4 local_c; // stack buffer fallback
    undefined4 local_8;
    undefined4 local_4;

    // Get pointer to free list or memory pool from this+4
    puVar1 = (undefined4*)this[1]; // this->freeList
    if (puVar1 == (undefined4*)0x0) {
        // No free list available, use stack buffer as temporary allocation
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        puVar1 = &local_c;
    }

    // Call virtual function at vtable[0] to allocate 0x24 bytes
    // The function takes size (0x24) and a pointer (puVar1) as arguments
    puVar1 = (undefined4*)(*(code *)**(undefined4**)*this)(0x24, puVar1);

    if (puVar1 != (undefined4*)0x0) {
        *puVar1 = local_4; // Initialize first field to 0
    }
    if (puVar1 + 1 != (undefined4*)0x0) {
        puVar1[1] = unaff_retaddr; // Store return address for debugging/tracking
    }
    if (puVar1 + 2 != (undefined4*)0x0) {
        puVar1[2] = &PTR_FUN_00d6ffac; // Set vtable pointer for allocated object
        puVar1[5] = 0; // +0x14: zero
        *(undefined2*)(puVar1 + 6) = 0; // +0x18: short zero
        *(undefined2*)((int)puVar1 + 0x1a) = 0; // +0x1a: short zero
        puVar1[8] = 0; // +0x20: zero
    }

    // Call initializer with param_2 (likely a constructor or setup function)
    FUN_007ec360(param_2);

    return puVar1;
}