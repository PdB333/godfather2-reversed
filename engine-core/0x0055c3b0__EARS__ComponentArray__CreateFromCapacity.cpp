// FUNC_NAME: EARS::ComponentArray::CreateFromCapacity
undefined4* __thiscall EARS::ComponentArray::CreateFromCapacity(void* allocContext, int* sourceObj) {
    // Get thread-local storage (likely current thread's heap context)
    TlsGetValue(DAT_01139810);

    // Allocate 0x20 bytes for the component array object header (tag 0xb)
    undefined4* newObj = (undefined4*)FUN_00aa2680(0x20, 0xb);

    // +0x04: header size (0x20)
    *(undefined2*)(newObj + 1) = 0x20;
    // +0x06: version or flags (1)
    *(undefined2*)((int)newObj + 6) = 1;
    // +0x08: first array pointer (null)
    newObj[2] = 0;
    // +0x0C: first array count (0)
    newObj[3] = 0;
    // +0x10: first array capacity (with high bit as allocation flag, actual capacity = value & 0x3FFFFFFF)
    newObj[4] = 0x80000000;
    // +0x00: vtable pointer
    *newObj = &PTR_FUN_00dc5428;

    // +0x14: second array pointer (null)
    int* array2Ptr = newObj + 5;
    *array2Ptr = 0;
    // +0x18: second array count (0)
    newObj[6] = 0;
    // +0x1C: second array capacity (with flag)
    newObj[7] = 0x80000000;

    // Call virtual function at vtable+0x220 on source object to get needed capacity
    int neededCapacity = (**(code**)(*sourceObj + 0x220))(sourceObj);

    // Ensure first array capacity meets requirement
    int maskedCap1 = newObj[4] & 0x3FFFFFFF;
    if (maskedCap1 < neededCapacity) {
        int newCap1 = maskedCap1 * 2;
        if (newCap1 <= neededCapacity) {
            newCap1 = neededCapacity;
        }
        // Resize first array (element size 0x30)
        FUN_00aa4110(newObj + 2, newCap1, 0x30);
    }
    newObj[3] = neededCapacity;

    // Ensure second array capacity meets requirement
    int maskedCap2 = newObj[7] & 0x3FFFFFFF;
    if (maskedCap2 < neededCapacity) {
        int newCap2 = maskedCap2 * 2;
        if (newCap2 <= neededCapacity) {
            newCap2 = neededCapacity;
        }
        // Resize second array (element size 0xC)
        FUN_00aa4110(newObj + 5, newCap2, 0xC);
    }
    newObj[6] = neededCapacity;

    // Constant used for initialization (likely 0 or -1)
    int initVal = DAT_00e2e780;
    int idx = 0;

    // Unrolled loop: initialize 4 elements at a time
    if (3 < neededCapacity) {
        int remain = (neededCapacity - 4) / 4 + 1;
        int off1 = 0;  // offset into first array
        int off2 = 0;  // offset into second array
        idx = remain * 4;

        do {
            // Initialize second array element (12 ints at offsets 0,4,8,0x0C,0x10,0x14,0x18,0x1C,0x20,0x24,0x28,0x2C)
            *(undefined4*)(off2 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 4 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 8 + *array2Ptr) = initVal;
            // First array: write to offset +0x20 within each element (4 elements per iteration)
            *(undefined4*)(off1 + 0x20 + *(newObj + 2)) = initVal;
            *(undefined4*)(off2 + 0x0C + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x10 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x14 + *array2Ptr) = initVal;
            *(undefined4*)(off1 + 0x50 + *(newObj + 2)) = initVal;
            *(undefined4*)(off2 + 0x18 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x1C + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x20 + *array2Ptr) = initVal;
            *(undefined4*)(off1 + 0x80 + *(newObj + 2)) = initVal;
            *(undefined4*)(off2 + 0x24 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x28 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 0x2C + *array2Ptr) = initVal;
            *(undefined4*)(off1 + 0xB0 + *(newObj + 2)) = initVal;

            off2 += 0x30;  // second array: 4 elements * 0xC each = 0x30
            off1 += 0xC0;  // first array: 4 elements * 0x30 each = 0xC0
            remain--;
        } while (remain != 0);
    }

    // Initialize remaining elements (less than 4)
    if (idx < neededCapacity) {
        int off1 = idx * 0x30;  // first array offset
        int off2 = idx * 0xC;   // second array offset
        int count = neededCapacity - idx;
        do {
            // For each remaining element, initialize second array (at offsets 0,4,8) and first array (+0x20)
            *(undefined4*)(off2 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 4 + *array2Ptr) = initVal;
            *(undefined4*)(off2 + 8 + *array2Ptr) = initVal;
            *(undefined4*)(off1 + 0x20 + *(newObj + 2)) = initVal;
            off2 += 0xC;
            off1 += 0x30;
            count--;
        } while (count != 0);
    }

    // Call further initialization (maybe base class constructor)
    FUN_00546960(allocContext, newObj);
    // Final post-construction setup (e.g., fill debug info)
    FUN_0055c5b0(newObj);
    return newObj;
}