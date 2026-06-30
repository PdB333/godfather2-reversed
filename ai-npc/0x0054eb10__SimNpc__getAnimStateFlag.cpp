// FUNC_NAME: SimNpc::getAnimStateFlag
int __fastcall SimNpc::getAnimStateFlag(int thisPtr)
{
  uint animState = *(uint *)(*(int *)(thisPtr + 0x18) + 0x2c);
  uint category = animState & 0xc0000000;
  if (category == 0) {
    // Category 0: return bit flag based on animState bits 5-9
    return 1 << ((byte)(animState >> 5) & 0x1f);
  }
  if (category != 0x40000000) {
    if (category != 0xc0000000) {
      // Category 0x80000000: return highest bit
      return -0x80000000;
    }
    // Category 0xC0000000: lookup in table at 0x54
    return *(int *)(animState * 4 + 0x54);
  }
  // Category 0x40000000: lookup in table at 0x8
  return *(int *)(animState * 4 + 8);
}