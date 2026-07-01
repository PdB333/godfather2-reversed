// FUNC_NAME: SomeClass::setField10
// Function address: 0x008c8160
// Role: Simple setter storing an undefined4 value at offset 0x10 (member variable)
// Called from 0x008fec30 and 0x008fdff0

void __thiscall SomeClass::setField10(SomeClass *this, undefined4 value)
{
    *(undefined4 *)((int)this + 0x10) = value; // store param_2 at +0x10
    return;
}