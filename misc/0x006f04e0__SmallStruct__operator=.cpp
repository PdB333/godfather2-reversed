// FUNC_NAME: SmallStruct::operator=
// Address: 0x006f04e0
// Copies two 32-bit members (8-byte struct) from source to target if different.

void __thiscall SmallStruct::operator=(SmallStruct *this, SmallStruct *other)
{
    if (this != other) {
        this->field_0 = other->field_0;  // +0x00
        this->field_4 = other->field_4;  // +0x04
    }
}