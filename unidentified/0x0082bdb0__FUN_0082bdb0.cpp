// FUNC_NAME: SomeClass::SomeClass
undefined4* __thiscall SomeClass::SomeClass(undefined4* this, byte constructorFlag)
{
    int* vtablePtr;
    
    // Set primary vtable pointer
    this[0] = &PTR_FUN_00d73790;
    // Call base class constructor
    FUN_0082a3c0();
    // Set secondary vtable pointer at offset 0x30 (0xc * 4)
    this[0xc] = &PTR_LAB_00e32854;
    // Additional member initialization
    FUN_00821f60();
    // If flag bit 0 is set, perform custom deallocation (likely for placement new)
    if ((constructorFlag & 1) != 0) {
        vtablePtr = (int*)FUN_009c8f80();
        // Call operator delete via vtable at offset 4 with size 0x100
        (**(code**)(*vtablePtr + 4))(this, 0x100);
    }
    return this;
}