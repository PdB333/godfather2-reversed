// FUNC_NAME: SomeClass::setSomeFlag
void __thiscall setSomeFlag(int this, char enable)
{
  if (enable != '\0') {
    // Set bit 6 (0x40) at offset +0x4c
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) | 0x40;
    return;
  }
  // Clear bit 6 (0x40) at offset +0x4c
  *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) & 0xffffffbf;
  return;
}