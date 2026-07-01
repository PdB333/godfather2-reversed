// FUNC_NAME: SomeClass::processEvent
undefined4 __thiscall SomeClass::processEvent(int* thisPtr, int* otherPtr)
{
    char cVar1;
    int iVar2;
    int unaff_ESI; // global or register variable
    char unaff_retaddr; // likely a parameter or stack variable
    undefined4 local_10; // interface pointer
    undefined1 uStack_c; // padding

    local_10 = 0;
    // Query interface from otherPtr using GUID 0xd80c71d2
    cVar1 = (**(code **)(*otherPtr + 0x10))(0xd80c71d2, &local_10);
    if ((cVar1 != '\0') && (unaff_ESI != 0)) {
        // Check if flag at offset 0xC88 (thisPtr[0x322]) has bit 4 set
        if ((thisPtr[0x322] | 4U) != thisPtr[0x322]) {
            // Call virtual function at offset 0x58 (thisPtr[0x16] + 0x28) with argument 0x10
            (**(code **)(thisPtr[0x16] + 0x28))(0x10);
            thisPtr[0x322] = thisPtr[0x322] | 4; // Set bit 4
        }
        local_10 = 0;
        uStack_c = 0;
        if (unaff_retaddr == '\0') {
            // Call stack allocation function (FUN_00408a00) with stack pointer and 0
            FUN_00408a00(&stack0xffffffec, 0);
            // Call cleanup/destructor on otherPtr
            FUN_00877d70(otherPtr);
            return 1;
        }
        FUN_00408a00(&stack0xffffffec, 0);
    }
    if (unaff_retaddr != '\0') {
        // Call virtual function at offset 0x1e4 from thisPtr's vtable
        iVar2 = (**(code **)(*thisPtr + 0x1e4))();
        if (iVar2 != 0) {
            return 0;
        }
        // Call virtual function at offset 0x20c from thisPtr's vtable with otherPtr
        (**(code **)(*thisPtr + 0x20c))(otherPtr);
    }
    // Call cleanup/destructor on otherPtr
    FUN_00877d70(otherPtr);
    return 1;
}