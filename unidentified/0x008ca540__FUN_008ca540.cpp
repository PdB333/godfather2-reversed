// FUNC_NAME: UnknownClass::initializeStreamResource
undefined4 * __thiscall UnknownClass::initializeStreamResource(
    undefined4 *this,
    undefined4 param2,
    int param3,
    undefined4 param4,
    undefined4 param5,
    undefined4 param6
) {
    // vtable pointer (likely to a stream or resource class)
    this[0] = &PTR_FUN_00d7bf50;
    this[1] = param2;                            // +0x04: store first argument
    this[2] = param3;                            // +0x08: store manager pointer

    // Initialize a local object via helper function
    undefined local_stack[76];                    // auStack_50, size 0x4C
    undefined4 uVar1 = (**(code **)(**(int **)(param3 + 8) + 0x1c))(); // call manager virtual method
    FUN_008ca470(local_stack, uVar1);            // init local with result

    // Thread-local storage for allocation context
    TlsGetValue(DAT_01139810);

    // Allocate 0x70 bytes (flag 0x27) – possibly a descriptor or small object
    int alloc1 = FUN_00aa2680(0x70, 0x27);
    *(short *)(alloc1 + 4) = 0x70;               // store size at offset +4

    // Create or obtain another object via param4 and param5
    undefined4 *obj2 = (undefined4 *)FUN_00a6bad0(param4, param5);

    TlsGetValue(DAT_01139810);

    // Allocate another block of 0x160 bytes (flag 0x31)
    int alloc2 = FUN_00aa2680(0x160, 0x31);
    *(short *)(alloc2 + 4) = 0x160;

    undefined4 uVar4 = FUN_0043b490();           // get some time/counter
    uVar4 = FUN_00540c60(param6, 0x1f, uVar4);   // possibly encode an ID
    uVar4 = FUN_009f0c70(obj2, local_stack, uVar4); // register/associate with obj2

    this[3] = uVar4;                             // +0x0C: store result

    // Decrement and possibly release obj2 if refcount reaches zero
    if (*(short *)(obj2 + 1) != 0) {
        *(short *)((int)obj2 + 6) = *(short *)((int)obj2 + 6) - 1;
        if (*(short *)((int)obj2 + 6) == 0) {
            (**(code **)*obj2)(1);               // call release/delete with flag 1
        }
    }

    FUN_0043b490();                              // redundant call
    FUN_009f01f0(0x2001, uVar1, 0);              // post event/message

    return this;
}