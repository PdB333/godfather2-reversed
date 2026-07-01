// FUNC_NAME: SomeClass::setTwoIntsAndFlag
void __thiscall SomeClass::setTwoIntsAndFlag(undefined4 *this, undefined4 firstInt, undefined4 secondInt, char flag)
{
  // +0x00: first integer field
  *this = firstInt;
  // +0x04: second integer field
  this[1] = secondInt;
  // +0x08: flags field (bit 0 used for the flag)
  if (flag != '\0') {
    this[2] = this[2] | 1;
    return;
  }
  this[2] = this[2] & 0xfffffffe;
  return;
}