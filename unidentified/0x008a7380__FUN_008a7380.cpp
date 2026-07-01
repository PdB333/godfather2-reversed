// FUNC_NAME: SomeClass::operator!=
// Function at 0x008a7380: Inequality operator comparing 7 integer fields (offsets +0x04..+0x1C).
// Returns true if any field differs; false if all equal.

bool __thiscall SomeClass::operator!=(const SomeClass& other) const
{
    // Compare fields stored at offsets +0x04, +0x08, +0x0C, +0x10, +0x14, +0x18, +0x1C
    if (this->field_04 == other.field_04 &&
        this->field_08 == other.field_08 &&
        this->field_0C == other.field_0C &&
        this->field_10 == other.field_10 &&
        this->field_14 == other.field_14 &&
        this->field_18 == other.field_18 &&
        this->field_1C == other.field_1C)
    {
        return false; // objects are equal
    }
    return true; // objects are not equal
}