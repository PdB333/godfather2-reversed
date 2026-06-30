// FUN_NAME: SomeGameObject::Constructor
// Address: 0x00700020
// Description: Constructor with flag parameter (bit0 controls additional initialization)
undefined4 __thiscall SomeGameObject::Constructor(undefined4 this, byte flag)
{
    // Call base class constructor
    BaseClass::Constructor(); // FUN_006ffe60

    // If flag's bit0 is set, call additional initialization
    if ((flag & 1) != 0) {
        AdditionalInit(this); // FUN_009c8eb0
    }

    return this;
}