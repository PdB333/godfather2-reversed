// FUNC_NAME: allocateAndInitializeNode
void __thiscall allocateAndInitializeNode(int this, int param_2) {
    // this points to an allocator object
    // +0x04: pointer to a function pointer (likely allocation routine)
    // +0x08: pointer to a fallback buffer (used if non-null, else stack local)
    // ESI register holds a pointer to source data (two DWORDs read)
    int* puVar1;
    int local_c;
    int local_8;
    int local_4;

    puVar1 = *(int**)(this + 8); // Get pointer to fallback buffer
    if (puVar1 == 0) {
        // No fallback buffer: use local stack as temporary
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        puVar1 = &local_c;
    }

    // Call allocation function: takes size (24 bytes) and a hint pointer
    // The function pointer is at the vtable offset of the allocator
    puVar1 = (int*)((*(code**)(*(int*)(this + 4)))[0])(0x18, puVar1);

    if (puVar1 != 0) {
        puVar1[0] = local_4;                       // +0x00: flags/type from local_4 (0 if no fallback)
        puVar1[1] = /*unaff_retaddr*/;             // +0x04: return address (likely continuation)
        puVar1[2] = param_2;                       // +0x08: parameter passed to function
        puVar1[3] = * /*unaff_ESI*/;               // +0x0C: first value from ESI source
        puVar1[4] = /*unaff_ESI[1]*/;              // +0x10: second value from ESI source
        *(char*)(puVar1 + 5) = 0;                  // +0x14: zero byte
        *(char*)((int)puVar1 + 0x15) = 0;          // +0x15: zero byte (size 0x18 = 24, structure padded)
    }
}