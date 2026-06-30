// FUNC_NAME: UnknownClass::UnknownClass

struct UnknownClass {
    void* vtable;       // +0x00
    int field_04;       // +0x04
    int field_08;       // +0x08
    int field_0C;       // +0x0C
    int field_10;       // +0x10
};

void __fastcall UnknownClass_Constructor(UnknownClass* thisPtr)
{
    int uVar1 = DAT_00e2eff4; // global initialization value

    thisPtr->field_04 = 0;
    thisPtr->vtable = &PTR_FUN_00e407c8; // vtable pointer
    thisPtr->field_08 = 0;
    thisPtr->field_0C = 0;
    thisPtr->field_10 = uVar1;
    return;
}