//FUNC_NAME: MemoryObject::MemoryObject
undefined4* MemoryObject::MemoryObject(undefined4* this, uint flags)
{
    undefined4* obj;
    int status;
    undefined4 uVar2;
    void* dst;
    size_t size; // unaff_EDI
    void* src;
    undefined4 allocFlags[2];

    if (this == (undefined4*)0x0) {
        allocFlags[0] = 2;
        allocFlags[1] = 0x10;
        // Allocate 16 bytes using custom allocator (DAT_01205868)
        obj = (undefined4*)(**(code**)*DAT_01205868)(0x10, allocFlags);
        obj[2] = obj; // +0x08: self-pointer
    } else {
        obj = this;
        obj[2] = 0; // +0x08: null if pre-allocated
    }
    dst = (void*)0x0;
    obj[1] = size; // +0x04: store size (from EDI)
    *(undefined1*)(obj + 3) = 0; // +0x0C: byte flag

    if ((flags & 4) != 0) {
        dst = (void*)0x20;
    }
    if ((flags & 8) != 0) {
        dst = (void*)((uint)dst | 0x200);
        *(undefined1*)(obj + 3) = 1; // set byte flag to 1
    }
    if ((flags & 0x10) != 0) {
        dst = (void*)((uint)dst | 8);
    }

    src = (void*)0x0;
    // Call global manager method at vtable+0x68 (DAT_01205750)
    status = (**(code**)(*DAT_01205750 + 0x68))(DAT_01205750);
    if (status == 0) {
        if (src != (void*)0x0) {
            uVar2 = 0;
            if (*(char*)(obj + 3) != '\0') {
                uVar2 = 0x3000;
            }
            // Call vtable method at +0x2c and +0x30 (unused in this path)
            (**(code**)(*(int*)*obj + 0x2c))((int*)*obj, 0, 0, &stack0xffffffec, uVar2);
            _memcpy(dst, src, size);
            (**(code**)(*(int*)*obj + 0x30))((int*)*obj);
        }
    } else if (status == -0x7789fe84) {
        // Error handling: call function at PTR_FUN_00f15a3c with argument 2
        (*(code*)PTR_FUN_00f15a3c)(2);
        return obj;
    }
    return obj;
}