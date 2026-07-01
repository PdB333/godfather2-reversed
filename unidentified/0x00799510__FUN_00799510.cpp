// FUNC_NAME: SomeClass::setOffsetPosition
void __thiscall setOffsetPosition(int thisPtr, int param_2, uint param_3)
{
  float fVar1;
  
  if (param_3 < 5) {
    fVar1 = (float)param_2;
    if (param_2 < 0) {
      fVar1 = fVar1 + DAT_00e44578; // 0x100000000 as float for unsigned conversion
    }
    // +0x2008: base position (likely a Vector3 or similar)
    // +0x3080: array of 5 float offsets (each 4 bytes)
    *(float *)(thisPtr + 0x3080 + param_3 * 4) = fVar1 + *(float *)(thisPtr + 0x2008);
  }
  return;
}