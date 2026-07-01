// FUNC_NAME: SomeClass::constructor
// Address: 0x00921660
// Calls base constructor at 0x00920fb0 and optionally calls extraInit at 0x005c4480

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte doExtraInit)
{
    // Call base class constructor
    BaseClass::constructor(this);
    
    // If the flag's lowest bit is set, perform additional initialization
    if ((doExtraInit & 1) != 0) {
        this->extraInit(); // Calls FUN_005c4480
    }
    
    return this;
}