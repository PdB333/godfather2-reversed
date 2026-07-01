// FUNC_NAME: SomeClass::setSomeFlag
void __thiscall SomeClass::setSomeFlag(int this, char param_2)
{
  // Check bit 7 of flags at offset +0x2BC (700 decimal)
  if ((*(uint *)(this + 700) >> 7 & 1) != 0) {
    return;
  }
  if (param_2 == '\0') {
    // Clear bit 28 (0x10000000) of flags at +0x2BC
    *(uint *)(this + 700) = *(uint *)(this + 700) & 0xefffffff;
    // Check bit 20 (0x100000) of flags at +0x2BC
    if ((*(uint *)(this + 700) >> 0x14 & 1) == 0) {
      FUN_00796120();
      return;
    }
  }
  else {
    // Set bit 28 (0x10000000) of flags at +0x2BC
    *(uint *)(this + 700) = *(uint *)(this + 700) | 0x10000000;
  }
  FUN_00796120();
  return;
}