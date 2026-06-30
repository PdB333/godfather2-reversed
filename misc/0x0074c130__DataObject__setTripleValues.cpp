// FUNC_NAME: DataObject::setTripleValues
void __thiscall DataObject::setTripleValues(uint64_t val1, uint64_t val2, uint64_t val3)
{
  // Store three 8-byte values at relative offsets 0x1c, 0x24, 0x2c
  this->field_0x1c = val1; // +0x1c
  this->field_0x24 = val2; // +0x24
  this->field_0x2c = val3; // +0x2c
}