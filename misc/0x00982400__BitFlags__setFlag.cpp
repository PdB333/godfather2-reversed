// FUNC_NAME: BitFlags::setFlag
void __thiscall BitFlags::setFlag(uint *flags, char enable)
{
  if (enable != '\0') {
    *flags = *flags | 4;          // Set bit 2 (0x4)
    return;
  }
  *flags = *flags & 0xfffffffb;   // Clear bit 2 (0x4)
  return;
}