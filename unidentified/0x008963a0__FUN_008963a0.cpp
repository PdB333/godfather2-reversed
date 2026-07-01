// FUNC_NAME: SomeClass::setThreeFields
void __thiscall SomeClass::setThreeFields(undefined4 *this, undefined4 a, undefined4 b, undefined4 c)
{
  // +0x00: field0
  *this = a;
  // +0x18 (index 6): field6
  this[6] = b;
  // +0x1C (index 7): field7
  this[7] = c;
  return;
}