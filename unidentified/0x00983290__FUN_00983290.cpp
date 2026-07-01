// FUNC_NAME: SomeClass::registerDataFields
void __fastcall SomeClass::registerDataFields(int this)
{
    // Call base class registration first
    FUN_005c1740();
    
    // Register data fields with offset, size, flags, etc.
    // param_1 + 0x54: field at offset 0x54, size 6 bytes
    FUN_005c01d0(&DAT_00d856e0, this + 0x54, 6, 0, 0, 1);
    
    // param_1 + 0x58: field at offset 0x58, size 6 bytes
    FUN_005c01d0(&DAT_00d8ca08, this + 0x58, 6, 0, 0, 1);
    
    // param_1 + 0x5c: field at offset 0x5c, size 4 bytes
    FUN_005c01d0(&DAT_00d8e6dc, this + 0x5c, 4, 0, 0, 1);
    
    return;
}