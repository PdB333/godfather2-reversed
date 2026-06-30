//FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(int *thisHandle, uint64 param2, uint64 param3, uint32 param4)
{
    int *objectPtr;
    int *vtablePtrSlot;

    // Dereference handle to get actual object pointer
    objectPtr = (int *)*thisHandle;

    // Write vtable pointer at offset +0x14 from object base
    *(void **)(objectPtr + 0x14) = (void *)&PTR_LAB_00e50c5c;

    // Increment the pointer at offset +0x14 by 4 (advance to next vtable slot?)
    vtablePtrSlot = (int *)(objectPtr + 0x14);
    *vtablePtrSlot = *vtablePtrSlot + 4;

    // Copy parameters to local buffer and call initialization routine
    // FUN_0049c430 likely performs memset or memcpy with size 0x14 and count 4
    uint64 localBuf[2]; // 16 bytes, but function expects 0x14*4=80 bytes? Possibly overflow, but follows decompiled logic
    localBuf[0] = param2;
    localBuf[1] = param3;
    uint32 localBuf2 = param4;
    FUN_0049c430(&localBuf, 0x14, 4);
}