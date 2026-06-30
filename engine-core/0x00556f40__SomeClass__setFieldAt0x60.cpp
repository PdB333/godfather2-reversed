// FUNC_NAME: SomeClass::setFieldAt0x60

// Address: 0x00556f40
// Simple setter that assigns an integer value to a member at offset 0x60 from 'this'.
// Only performs assignment if the new value differs from the current one.
void __thiscall SomeClass::setFieldAt0x60(int value) {
    // +0x60: member field (likely a pointer or ID) being set
    if (this->field_0x60 != value) {
        this->field_0x60 = value;
    }
}