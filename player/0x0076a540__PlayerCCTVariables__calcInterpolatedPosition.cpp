// FUNC_NAME: PlayerCCTVariables::calcInterpolatedPosition
void __thiscall calcInterpolatedPosition(int thisPtr, float *outPos)
{
  float fVar1;
  int iVar2;
  int *piVar3;
  float unaff_ESI; // unknown register saved from caller
  float local_2c; // this+0x7c ?
  float fStack_28;
  float fStack_24;
  float fStack_20;
  undefined4 uStack_1c;

  // Derived from this+0x70, offset from some base object
  if (*(int *)(thisPtr + 0x70) == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)(*(int *)(thisPtr + 0x70) + -0x48);
  }
  // Virtual call to get something (likely world position) +0xa4 over vtable
  (**(code **)(*piVar3 + 0xa4))(&local_2c);

  // Get the player camera or control target location? +0x30 is likely a position vector
  iVar2 = FUN_00471610(); // likely getPlayerControlTarget() or getCamera()
  fStack_28 = *(float *)(iVar2 + 0x30) - (float)(thisPtr + 0x7c);
  fStack_24 = *(float *)(iVar2 + 0x34) - unaff_ESI;
  fStack_20 = *(float *)(iVar2 + 0x38) - local_2c;
  uStack_1c = 0;

  // Normalize the difference vector
  FUN_0056afa0(&fStack_28, &fStack_28); // likely vectorNormalize

  fVar1 = *(float *)(thisPtr + 0x80); // interpolation factor
  *outPos = fStack_28 * fVar1 + (float)(thisPtr + 0x7c);
  outPos[1] = fStack_24 * fVar1 + unaff_ESI;
  outPos[2] = fStack_20 * fVar1 + local_2c;
  return;
}