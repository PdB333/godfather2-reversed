// FUNC_NAME: SomeClass::constructor
void* __thiscall SomeClass::constructor(void* thisPtr, byte allocationFlag)
{
    // Set vtable pointers for multiple inheritance
    *(void(***)(void))thisPtr = (void(***)(void))&PTR_FUN_00d7f1c0;          // main vtable at +0x00
    *(void(***)(void))((char*)thisPtr + 0x3C) = (void(***)(void))&PTR_LAB_00d7f1b0; // +0x3C
    *(void(***)(void))((char*)thisPtr + 0x48) = (void(***)(void))&PTR_LAB_00d7f1ac; // +0x48
    *(void(***)(void))((char*)thisPtr + 0x50) = (void(***)(void))&PTR_LAB_00d7f1a8; // +0x50
    *(void(***)(void))((char*)thisPtr + 0x54) = (void(***)(void))&PTR_LAB_00d7f148; // +0x54
    *(void(***)(void))((char*)thisPtr + 0x58) = (void(***)(void))&PTR_LAB_00d7f0e0; // +0x58

    // Initialize common member data
    initializeClass();  // FUN_008ded50

    // If allocationFlag's lowest bit is set, deallocate the object (e.g. failed allocation cleanup)
    if ((allocationFlag & 1) != 0) {
        deallocateMemory(thisPtr, 0x220);  // FUN_0043b960 — likely operator delete(size 0x220)
    }

    return thisPtr;
}