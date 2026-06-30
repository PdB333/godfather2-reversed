// FUNC_NAME: SomeClass::compareWith
// Address: 0x00693c10
// Role: Compares two objects of a class with two integer fields (offset 0 and offset 4).
// Asserts that this->field0 is non-zero and equals other->field0 (via FUN_00b97aea).
// Returns a composite value: lower 24 bits = (this->field1 >> 8), high byte = (this->field1 != other->field1).

int __thiscall SomeClass::compareWith(SomeClass* this, SomeClass* other)
{
    // +0x00: field0 (used as a key/type ID)
    // +0x04: field1 (some value)
    if ((this->field0 == 0) || (this->field0 != other->field0))
    {
        FUN_00b97aea(); // Assertion failure
    }
    // Construct result: combine shifted field1 with equality flag
    return ((int)((uint)this->field1 >> 8) & 0xFFFFFF) | ((this->field1 != other->field1) << 24);
}