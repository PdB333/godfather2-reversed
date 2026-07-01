// FUNC_NAME: Sentient::setDamageFlags
void __thiscall Sentient::setDamageFlags(int this, byte flag1, byte flag2, byte flag3)
{
  *(byte *)(this + 0x150) = flag1;
  *(byte *)(this + 0x152) = flag3;
  *(byte *)(this + 0x151) = flag2;
  *(uint *)(this + 0x11c) = *(uint *)(this + 0x11c) | 0x80000; // +0x11c: damageFlags bitfield, set bit 19
  if (*(int *)(&DAT_00e56a9c + *(int *)(this + 4) * 0x2c) == 1) { // +0x04: some type/class ID, DAT_00e56a9c is likely a global array of structs (0x2c bytes each)
    FUN_00948ee0(); // likely handleDamageType1
    return;
  }
  if (*(int *)(&DAT_00e56a9c + *(int *)(this + 4) * 0x2c) == 2) {
    FUN_00948f60(); // likely handleDamageType2
  }
  return;
}