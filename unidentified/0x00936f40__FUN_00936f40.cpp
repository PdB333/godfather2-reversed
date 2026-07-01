// FUNC_NAME: SomeClass::init
void __fastcall SomeClass::init(int this) {
    // Call base class or global initialization
    FUN_005c1740();
    // Register this object with a global list/manager at DAT_00d873d4
    // The second argument is a pointer to a member at offset +0x50
    FUN_005c01d0(&DAT_00d873d4, this + 0x50, 1, 0, 0, 0);
}