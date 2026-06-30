// FUNC_NAME: SomeClass::setReference
void __thiscall SomeClass::setReference(uint *this, uint target)
{
  // Store the target pointer at offset +8 (this[2])
  this[2] = target;
  if (target != 0) {
    // Check byte at target+0x54 (some boolean flag)
    if (*(char *)(target + 0x54) == '\0') {
      // Clear bit 0 (flag 0x1)
      *this = *this & 0xfffffffe;
    }
    else {
      // Set bit 0 (flag 0x1)
      *this = *this | 1;
    }
    // Check byte at target+0x55 (another boolean flag)
    if (*(char *)(target + 0x55) != '\0') {
      // Set bit 7 (flag 0x80)
      *this = *this | 0x80;
      return;
    }
    // Clear bit 7 (flag 0x80)
    *this = *this & 0xffffff7f;
  }
  return;
}