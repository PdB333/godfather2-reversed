// FUNC_NAME: CoverState::setCoverReference
void __thiscall CoverState::setCoverReference(int thisPtr, int coverObjPtr)
{
  if (coverObjPtr == 0 || *(int *)(coverObjPtr + 0x20) == 0) {
    *(int *)(thisPtr + 100) = 0; // +0x64
    *(int *)(thisPtr + 0x60) = 0;
    *(int *)(thisPtr + 0x5c) = 0;
    *(int *)(thisPtr + 0x58) = 0;
  }
  else {
    *(int *)(thisPtr + 0x58) = *(int *)(coverObjPtr + 0x20); // Position/transform data
    *(int *)(thisPtr + 0x5c) = *(int *)(coverObjPtr + 0x24);
    *(int *)(thisPtr + 0x60) = *(int *)(coverObjPtr + 0x28);
    *(int *)(thisPtr + 100) = *(int *)(coverObjPtr + 0x2c);
    int uVar1 = FUN_0043b490(); // Likely GetSomeTimeValue or similar
    *(int *)(thisPtr + 0x150) = uVar1; // Timer or timestamp
    *(int *)(thisPtr + 0x108) |= 8; // +0x108 bitfield flag for "hasCoverReference"
    if (*(int *)(thisPtr + 0x54) == 5 || *(int *)(thisPtr + 0x54) == 6) { // State 5 or 6 (cover states?)
      if (*(int *)(thisPtr + 0x148) != 0) {
        CoverState::applyCoverEffect(*(int *)(thisPtr + 0x148), coverObjPtr);
        return;
      }
      if (((*(int *)(thisPtr + 0x108) >> 1 & 1) != 0) && ((*(int *)(thisPtr + 0x108) >> 2 & 1) == 0)) {
        FUN_00947510(); // Possibly playCoverAnimation or similar
        return;
      }
    }
  }
  return;
}