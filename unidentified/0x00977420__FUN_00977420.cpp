// FUNC_NAME: SomeClass::getSomeField
undefined4 __fastcall SomeClass::getSomeField(int this)
{
    // Returns the value at offset 0x13C from the object pointer.
    // This is likely a simple getter for a member variable.
    return *(undefined4 *)(this + 0x13c);
}