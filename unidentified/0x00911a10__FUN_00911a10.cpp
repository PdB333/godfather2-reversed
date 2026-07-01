// FUNC_NAME: SomeClass::initSomeFields
void __fastcall SomeClass::initSomeFields(int this)
{
    // Call some initialization function
    FUN_005c1740();
    
    // Copy 4 bytes from global DAT_00d83fd4 to this+0x54
    FUN_005c01d0(&DAT_00d83fd4, this + 0x54, 4, 0, 0, 0);
    
    // Copy 4 bytes from global DAT_00d83fd0 to this+0x58
    FUN_005c01d0(&DAT_00d83fd0, this + 0x58, 4, 0, 0, 0);
    
    return;
}