// FUNC_NAME: SomeClass::init
void __thiscall SomeClass::init(void)
{
    // Call subsystem initialization functions
    this->initSubsystem1();  // FUN_0097cd60
    this->initSubsystem2();  // FUN_0097ce70
    this->initSubsystem3();  // FUN_0097cf90
    this->initSubsystem4();  // FUN_0097d100

    // Set bit 1 (value 2) in flags at offset 0x102 to mark initialization complete
    *(ushort *)((int)this + 0x102) |= 2;
}