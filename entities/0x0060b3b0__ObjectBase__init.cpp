// FUNC_NAME: ObjectBase::init
undefined4* __thiscall ObjectBase::init(undefined4* this, uint flags)
{
    undefined4* allocatedObj;
    void* dst;
    int result;
    undefined4 uVar2;
    undefined4 local_c;
    undefined4 local_8;

    if (this == (undefined4*)0x0) {
        local_c = 2;                 // memory pool identifier
        local_8 = 0x10;             // allocation size (16 bytes)
        allocatedObj = (undefined4*)(**(code**)*DAT_01205868)(0x10, &local_c); // allocate from global heap
        allocatedObj[2] = allocatedObj; // +0x8: self-pointer
    } else {
        allocatedObj = this;
        allocatedObj[2] = (undefined4*)0x0; // +0x8: null
    }
    dst = (void*)0x0;
    allocatedObj[1] = (uint)unaff_EDI; // +0x4: store size/count (register EDI value)
    *(undefined1*)(allocatedObj + 3) = 0; // +0xC: byte flags = 0
    if ((flags & 4) != 0) {
        dst = (void*)0x20;               // OS alloc flag: 0x20 (FILE_FLAG_NO_BUFFERING?)
    }
    if ((flags & 8) != 0) {
        dst = (void*)((uint)dst | 0x200); // add 0x200 (FILE_FLAG_OVERLAPPED?)
        *(undefined1*)(allocatedObj + 3) = 1; // +0xC: byte flag = 1
    }
    if ((flags & 0x10) != 0) {
        dst = (void*)((uint)dst | 8);    // add 0x8 (FILE_ATTRIBUTE_NORMAL?)
    }
    // Dead code below: _Src is always 0, so inner block never executes
    // The function call through vtable likely queries capability
    result = (**(code**)(*DAT_01205750 + 0x68))(DAT_01205750);
    if (result == 0) {
        // _Src remains 0, so this never runs
        if (_Src != (void*)0x0) {
            uVar2 = 0;
            if (*(char*)(allocatedObj + 3) != '\0') {
                uVar2 = 0x3000;
            }
            (**(code**)(*(int*)*allocatedObj + 0x2c))((int*)*allocatedObj, 0, 0, &stack0xffffffec, uVar2);
            _memcpy(dst, _Src, unaff_EDI);
            (**(code**)(*(int*)*allocatedObj + 0x30))((int*)*allocatedObj);
        }
    } else if (result == (int)-0x7789fe84) { // 0x8876017C – specific error code
        (*(code*)PTR_FUN_00f15a3c)(2);       // error handler
        return allocatedObj;
    }
    return allocatedObj;
}