// FUNC_NAME: NetConnection::buildPacketData

void __thiscall NetConnection::buildPacketData(void *this, int param_1) {
    int bufferSize; // local_b0, originally from this+8
    int *ptr; // local_8c
    uint count; // uVar5, from param_1+0xc4
    int idx;
    int j;
    uint size;
    int *arr;
    int someSize;
    int local_90;
    uint local_88;
    uint local_84;
    int *local_80;
    uint local_7c;
    int local_78;
    char local_74[4];
    int local_70[3];
    char local_63;

    bufferSize = *(int *)((char *)this + 8);
    local_63 = *(char *)(param_1 + 0xb0);
    local_70[0] = *(int *)(param_1 + 0x9c);
    // Call virtual method at offset +0x20, vtable index 3 (0xc)
    (*(void (__thiscall *)(void *))(*(int **)(param_1 + 0x20) + 3))(this); // ??? not sure what this call does

    count = *(uint *)(param_1 + 0xc4);
    local_90 = *(int *)(param_1 + 0xbc);
    *(char *)(param_1 + 0xb0) = local_74[1]; // suspicious: local_74 is uninitialized? Might be stack garbage.
    ptr = 0;
    local_88 = 0;
    local_84 = 0x80000000;

    if (0 < (int)count) {
        // Allocate buffer for count entries? Size seems to be count itself (array of ints)
        FUN_00aa4110(&ptr, ((int)count < 0) - 1 & count);
    }

    // Copy array from param_1+0xc0 into allocated buffer
    for (idx = 0; idx < *(int *)(param_1 + 0xc4); idx++) {
        *(int *)(ptr + idx) = *(int *)(*(int *)(param_1 + 0xc0) + idx * 4);
    }

    // Call virtual at +0x24, vtable index 3
    // unaff_ESI is likely the buffer we just filled? But it's passed as first arg? Actually (**(code **)(**(int **)(param_1 + 0x24) + 0xc))(unaff_ESI, param_1);
    // unaff_ESI is unknown. It might be the buffer ptr? But not set. Possibly a leftover from previous call? The caller may have set it.
    // We'll assume it's a parameter that should be passed in ECX? Actually this call uses two parameters: unaff_ESI and param_1.
    // For now, we'll use a placeholder.
    {
        // The function called is likely another method that modifies the buffer.
        void *vtable = *(void **)(param_1 + 0x24);
        void (*func)(void *, void *) = *(void (**)(void *, void *))((int)vtable + 0xc);
        func((void *)unaff_ESI, (void *)param_1); // unaff_ESI is unknown
    }

    // Copy back from unaff_ESI to param_1+0xc0
    for (idx = 0; idx < *(int *)(param_1 + 0xc4); idx++) {
        *(int *)(*(int *)(param_1 + 0xc0) + idx * 4) = *(int *)(unaff_ESI + idx * 4);
    }

    // Set fields
    *(int *)(param_1 + 0xbc) = (int)unaff_EDI; // unaff_EDI uninitialized
    *(int *)(param_1 + 0x11c) = (int)unaff_EDI; // again unaff_EDI

    // Prepare a structure for next call
    local_70[0] = *(int *)(param_1 + 0xd0);
    *(int *)(param_1 + 0xcc) = *(char *)(*(int *)(param_1 + 0x1c) + 0x20); // this is a weird assignment, probably a bitfield
    *(short *)(param_1 + 0xcd) = *(short *)((char *)param_1 + 0xcd); // actually it's set from local_74 via CONCAT22? The decompiler shows:
    // uStack_74 = CONCAT22(*(undefined2 *)(param_1+0xcd), CONCAT11(*(undefined1 *)(param_1+0xcc), *(undefined1 *)(*(int *)(param_1+0x1c)+0x20)));
    // Then later: *(undefined1 *)(param_1 + 0xce) = uStack_80._3_1_; etc.
    // This is messy due to stack reuse.

    // Call virtual at +0x2c, vtable index 3
    (*(void (__thiscall *)(void *))(*(int **)(param_1 + 0x2c) + 3))((void *)iStack_ac); // iStack_ac is param_1? Actually iStack_ac = param_1.

    // Set fields from local variables
    *(char *)(param_1 + 0xce) = ((char *)&local_80)[3]; // uStack_80._3_1_ is the 4th byte of local_80
    *(uint *)(param_1 + 0xd0) = local_7c;
    bufferSize = *(int *)(param_1 + 0xb8);
    *(char *)(param_1 + 0xcc) = ((char *)&local_80)[1];
    *(char *)(param_1 + 0xcd) = ((char *)&local_80)[2];

    // Another virtual call at +0x28
    (*(void (__thiscall *)(int, int, int, int *, int **))(*(int **)(param_1 + 0x28) + 3))
        ((int)&local_80, param_1, (int)&stack0xffffff64, &ptr, &piStack_b4);

    // More buffer management
    uint count2 = *(uint *)(param_1 + 0xa4);
    *(int **)(param_1 + 0xb8) = &local_80;
    *(int *)(param_1 + 0xb4) = param_1;
    ptr = 0;
    local_88 = 0;
    local_84 = 0x80000000;
    local_80 = 0;
    local_7c = 0;
    local_78 = 0x80000000;

    if (0 < (int)count2) {
        FUN_00aa4110(&local_80, ((int)count2 < 0) - 1 & count2, 1);
    }

    int count3 = *(int *)(param_1 + 0xa4);
    local_7c = count2;
    if ((int)(local_84 & 0x3fffffff) < count3) {
        int newSize = (local_84 & 0x3fffffff) * 2;
        if (newSize <= count3) {
            newSize = count3;
        }
        FUN_00aa4110(&ptr, newSize, 4);
    }

    // Copy byte array from param_1+0xa0 to local_80 buffer
    for (idx = 0; idx < *(int *)(param_1 + 0xa4); idx++) {
        *(char *)(local_80 + idx) = *(char *)(idx + *(int *)(param_1 + 0xa0));
    }

    local_74[0] = *(char *)(param_1 + 0xac); // store byte
    *(int *)(param_1 + 0xac) = (int)local_74; // overflow? Actually the decompiler shows uStack_74 = *(undefined4 *)(param_1+0xac); later used.

    // Virtual call at +0x30
    (*(void (__thiscall *)(int, int, int *, int *))(*(int **)(param_1 + 0x30) + 3))
        (iVar3, param_1, piVar6, &ptr);

    // Copy back from temporary buffer to param_1+0xa0
    for (idx = 0; idx < ptr; idx++) {
        *(char *)(idx + *(int *)(param_1 + 0xa0)) = *(char *)(iStack_90 + idx);
    }

    // Copy from unaff_ESI to param_1+0x124 (array of ints)
    for (idx = 0; idx < unaff_EBX; idx++) {
        *(int *)(*(int *)(param_1 + 0x124) + idx * 4) = *(int *)(unaff_ESI + idx * 4);
    }

    // Store final size
    *(uint *)(param_1 + 0xac) = local_84;

    // Virtual call at +0x34
    (*(void (__thiscall *)(int, int, int, int))(*(int **)(param_1 + 0x34) + 3))
        (iVar1, param_1, *(int *)(param_1 + 0x118), *(int *)(param_1 + 0x120));

    // Virtual call at +0x38
    (*(void (__thiscall *)(int, int, int *))(*(int **)(param_1 + 0x38) + 3))
        (iVar2, param_1, &iStack_90);

    // Store final results to param_1 fields at +0x130..0x14c
    *(int *)(param_1 + 0x130) = (int)unaff_ESI;
    *(int *)(param_1 + 0x134) = unaff_EBX;
    *(int *)(param_1 + 0x138) = (int)uStack_94; // uninitialized?
    *(int *)(param_1 + 0x13c) = iStack_90;
    *(int *)(param_1 + 0x140) = (int)ptr;
    *(uint *)(param_1 + 0x144) = local_88;
    *(uint *)(param_1 + 0x148) = local_84;
    *(int *)(param_1 + 0x14c) = (int)local_80;

    // Clear array if some condition (field at +0x10c == 2)
    if (*(int *)(param_1 + 0x10c) == 2) {
        int entryCount = *(int *)(param_1 + 0x4c);
        for (idx = 0; idx < entryCount; idx++) {
            int base = *(int *)(param_1 + 0x48) + idx * 0xc0;
            *(int *)(base + 0xa8) = 0;
            *(int *)(base + 0xac) = 0;
            *(int *)(base + 0xb4) = 0;
            *(int *)(base + 0xb0) = 0;
        }
    }

    // Deallocate buffers if they were allocated (negative check for some flag)
    // puStack_a4 is local_70, which was set from param_1+0x9c earlier
    if (0 <= (int)local_70[0]) {
        uint flag = (uint)local_70[0] & 0x3fffffff;
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(param_1, flag, 0x17);
    }
    if (0 <= bufferSize) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(&local_80, bufferSize * 4, 0x17);
    }
    if (0 <= (int)&local_80) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(piVar6, (int)&local_80 * 4, 0x17);
    }
}