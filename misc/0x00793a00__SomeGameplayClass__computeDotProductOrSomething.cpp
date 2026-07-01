// FUNC_NAME: SomeGameplayClass::computeDotProductOrSomething
float __thiscall SomeGameplayClass::computeDotProductOrSomething(int thisPtr, int otherPtr)
{
  float dx, dy, dz;
  float otherDx, otherDy, otherDz;
  int someHandle1, someHandle2, someHandle3, someHandle4, someHandle5;

  if (otherPtr != thisPtr) {
    someHandle1 = FUN_00471610(); // likely getSomeComponent or getTransform
    someHandle2 = FUN_00471610();
    // +0x30 = position.x, +0x34 = position.y, +0x38 = position.z
    dx = *(float *)(someHandle2 + 0x30);
    dy = *(float *)(someHandle1 + 0x30);
    dz = *(float *)(someHandle2 + 0x34);
    // Note: This looks like a bug or intentional reuse - dy and dz are from different handles
    // Actually it's computing difference vectors between two positions
    float pos1x = *(float *)(someHandle1 + 0x30);
    float pos1y = *(float *)(someHandle1 + 0x34);
    float pos1z = *(float *)(someHandle1 + 0x38);
    float pos2x = *(float *)(someHandle2 + 0x30);
    float pos2y = *(float *)(someHandle2 + 0x34);
    float pos2z = *(float *)(someHandle2 + 0x38);
    
    someHandle3 = FUN_00471610(); // get another component
    someHandle4 = FUN_00471610();
    someHandle5 = FUN_00471610();
    // +0x20, +0x24, +0x28 are likely direction/vector components
    return (float)*(float *)(someHandle5 + 0x28) * (pos2z - pos1z) +
           (float)*(float *)(someHandle3 + 0x20) * (pos2x - pos1x) +
           (float)*(float *)(someHandle4 + 0x24) * (pos2y - pos1y);
  }
  // If comparing to self, check a flag at offset 700 (0x2BC)
  if ((*(uint *)(thisPtr + 700) >> 0x1e & 1) == 0) {
    return (float)_DAT_00d5780c; // likely a global constant (e.g., 0.0f or 1.0f)
  }
  return (float)DAT_00d5ccf8; // another global constant
}