// FUNC_NAME: EARSObjectBase::destroyTwoSubObjects
void __fastcall EARSObjectBase::destroyTwoSubObjects(EARSObjectBase* this) {
    int* piVar1;
    int iVar2;

    // Set initial vtable pointer (likely the original derived class vtable)
    *this = &PTR_FUN_00e36cb8; // +0x00: vtable pointer

    piVar1 = &this->subObject1; // +0x04: first sub-object pointer (offset +4)
    iVar2 = 2; // Two sub-objects to process

    do {
        // If the sub-object pointer is non-null, call its first vtable function (destructor/release) with argument 1
        if (*piVar1 != 0) {
            (*(code (**)(int))*piVar1)(1); // Call destructor/release on sub-object
        }
        piVar1 = piVar1 + 1; // Advance to next sub-object slot
        iVar2 = iVar2 - 1;
    } while (iVar2 != 0);

    // Switch to base class vtable (likely after destruction)
    *this = &PTR_LAB_00e36cbc; // +0x00: new vtable (base or default)

    // Reset global counter (likely a reference count or initialization flag)
    DAT_01223398 = iVar2; // iVar2 is 0 after loop, so global = 0
}