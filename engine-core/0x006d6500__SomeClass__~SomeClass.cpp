// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(int* thisPtr)
{
    // vtable pointer at +0x0
    *thisPtr = (int)&PTR_FUN_00d5f500;
    // secondary vtable or interface pointer at +0x8
    thisPtr[2] = (int)&PTR_LAB_00d5f4f8;

    // Release sub-objects if they exist
    // Sub-object pointer at offset +0x260 (thisPtr[0x98])
    if (thisPtr[0x98] != 0) {
        FUN_004daf90(thisPtr + 0x98);  // likely operator delete or release
    }
    // Sub-object pointer at offset +0x17C (thisPtr[0x5F])
    if (thisPtr[0x5F] != 0) {
        FUN_004daf90(thisPtr + 0x5F);
    }
    // Sub-object pointer at offset +0x174 (thisPtr[0x5D])
    if (thisPtr[0x5D] != 0) {
        FUN_004daf90(thisPtr + 0x5D);
    }
    // Sub-object pointer at offset +0xF0 (thisPtr[0x3C])
    if (thisPtr[0x3C] != 0) {
        FUN_004daf90(thisPtr + 0x3C);
    }
    // Sub-object pointer at offset +0xE8 (thisPtr[0x3A])
    if (thisPtr[0x3A] != 0) {
        FUN_004daf90(thisPtr + 0x3A);
    }

    // Final cleanup (maybe base destructor)
    FUN_006c9820();
    return;
}