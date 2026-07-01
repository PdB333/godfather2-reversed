// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(SomeClass *this) // 0x007d4390
{
    int *pData; // eax

    pData = this->field_0x24; // +0x24 (param_1[9])
    this->vtable = &PTR_FUN_00d6efa0; // set vtable to derived class vtable

    if (pData != 0) {
        if (*(int *)(pData + 8) != 0) { // +0x08 check if some sub-object exists
            FUN_009e7530(pData); // release sub-object
        }
        FUN_009f01a0(); // cleanup function
    }

    this->vtable = &PTR___purecall_00e407a4; // set vtable to purecall (base class destructor)
    return;
}