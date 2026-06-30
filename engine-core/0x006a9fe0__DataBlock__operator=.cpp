// FUNC_NAME: DataBlock::operator=
int __thiscall DataBlock::operator=(DataBlock *this, DataBlock *other)
{
  if (this != other) { // Self-assignment guard
    // Copy four 16-byte subobjects (strings? objects?) at offsets +4, +0x14, +0x24, +0x34
    copySubobject(&this->field_4, &other->field_4); // +0x04
    copySubobject(&this->field_0x14, &other->field_0x14); // +0x14
    copySubobject(&this->field_0x24, &other->field_0x24); // +0x24
    copySubobject(&this->field_0x34, &other->field_0x34); // +0x34
    // Copy four 4-byte floats (or ints) at offsets +0x44, +0x4C, +0x54, +0x5C
    copyFloat(&this->field_0x44, &other->field_0x44); // +0x44
    copyFloat(&this->field_0x4C, &other->field_0x4C); // +0x4C
    copyFloat(&this->field_0x54, &other->field_0x54); // +0x54
    copyFloat(&this->field_0x5C, &other->field_0x5C); // +0x5C
    // Copy integer at +100 (0x64) and byte at +0x68
    this->field_0x64 = other->field_0x64; // +0x64 (int)
    this->field_0x68 = other->field_0x68; // +0x68 (byte)
  }
  return (int)this;
}