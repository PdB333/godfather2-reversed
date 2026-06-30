// FUNC_NAME: SomeClass::setField
// Address: 0x004b7ce0
// Role: Simple setter that assigns an integer value to the first field of an object.
// The caller at 0x0099c5d0 suggests this is used to initialize or update a member variable.
void __thiscall SomeClass::setField(int value) {
    // +0x00: First dword of the object (likely an identifier, counter, or state flag)
    this->field = value;  // Directly assign the incoming value
    return;
}