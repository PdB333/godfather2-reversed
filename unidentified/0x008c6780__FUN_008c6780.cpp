// FUNC_NAME: SomeClass::setSomeFlag
void __thiscall SomeClass::setSomeFlag(int this, char param_2)
{
  // Check if some magic value at +0x54 is not 0x637b907 (likely a state or type check)
  if ((*(int *)(this + 0x54) != 0x637b907) &&
     // Compare bit 6 of the flags at +0x84 with the boolean value of param_2
     ((bool)((byte)(*(uint *)(this + 0x84) >> 6) & 1) != (param_2 == '\0'))) {
    // If param_2 is false (0), set bit 6 of the flags
    if (param_2 == '\0') {
      *(uint *)(this + 0x84) = *(uint *)(this + 0x84) | 0x40;
      // Call another function (likely to update state or trigger behavior)
      FUN_008c63b0();
      return;
    }
    // If param_2 is true (non-zero), clear bit 6 of the flags
    *(uint *)(this + 0x84) = *(uint *)(this + 0x84) & 0xffffffbf;
  }
  return;
}