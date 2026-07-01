// FUNC_NAME: SomeClass::initOrReset
void __fastcall SomeClass::initOrReset(int thisPtr)
{
    // Call initialization function with two parameters from the object's fields
    // +0x04: first field (likely a pointer or handle)
    // +0x08: second field (likely a pointer or handle)
    FUN_00887870(*(undefined4 *)(thisPtr + 4), *(undefined4 *)(thisPtr + 8));
    
    // Set a status/flag field to 0 (likely "not started" or "inactive")
    // +0x0C: status/flag field
    *(undefined4 *)(thisPtr + 0xc) = 0;
    
    return;
}