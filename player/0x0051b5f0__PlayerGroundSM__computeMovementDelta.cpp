// FUNC_NAME: PlayerGroundSM::computeMovementDelta
undefined4 FUN_0051b5f0(int this, float *outParams)

{
  float *pfVar1;
  uint flags;
  int iVar3;
  undefined4 result;
  int unaff_ESI;
  float fVar5;
  double dVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float local_40;
  float local_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  flags = *(uint *)(*(int *)(unaff_ESI + 0x10) + 0x14); // +0x10: some object, +0x14: flags
  if ((flags & 0x4000) == 0) {
    if (*(int *)(unaff_ESI + 0xbc) == 0) { // +0xBC: maybe attached entity?
      local_20 = *(float *)(unaff_ESI + 0x60); // +0x60: position x
      fStack_1c = *(float *)(unaff_ESI + 100); // +0x64: position y
      fStack_18 = *(float *)(unaff_ESI + 0x68); // +0x68: position z
      fStack_14 = *(float *)(unaff_ESI + 0x6c); // +0x6C: position w (unused)
    }
    else {
      FUN_0056b420(unaff_ESI + 0x30,*(int *)(unaff_ESI + 0xbc),&local_20); // get world position of attached
    }
  }
  else {
    local_20 = *(float *)(this + 0x70) + *(float *)(this + 0x60); // this+0x60: base pos, +0x70: offset
    fStack_1c = *(float *)(this + 0x74) + *(float *)(this + 100);
    fStack_18 = *(float *)(this + 0x78) + *(float *)(this + 0x68);
    fStack_14 = *(float *)(this + 0x7c) + *(float *)(this + 0x6c);
  }
  local_30 = local_20 - *(float *)(this + 0x70); // delta from target position
  fStack_2c = fStack_1c - *(float *)(this + 0x74);
  fStack_28 = fStack_18 - *(float *)(this + 0x78);
  fStack_24 = fStack_14 - *(float *)(this + 0x7c);
  fVar7 = SQRT(fStack_2c * fStack_2c + fStack_28 * fStack_28 + local_30 * local_30); // distance to target
  fVar5 = *(float *)(this + 100) * fStack_2c; // dot product components
  fVar9 = *(float *)(this + 0x68) * fStack_28;
  fVar10 = *(float *)(this + 0x60) * local_30;
  local_40 = DAT_00e2b1a4; // max speed
  if (*(float *)(this + 0x144) <= fVar7 && fVar7 != *(float *)(this + 0x144)) { // +0x144: min distance
    dVar6 = (double)(*(float *)(this + 0x14c) * DAT_00e2cd54); // +0x14C: acceleration
    FUN_00b9c041(); // some math function (maybe sin/cos?)
    local_40 = *(float *)(unaff_ESI + 0x88) / // +0x88: max speed
               ((float)dVar6 * fVar7 * DAT_00e2b1a0 + (float)PTR_FUN_00e4462c);
    if (0.0 <= local_40) {
      fVar8 = DAT_00e2b1a4;
      if (local_40 <= DAT_00e2b1a4) goto LAB_0051b73b;
    }
    else {
      fVar8 = 0.0;
    }
    local_40 = fVar8;
  }
LAB_0051b73b:
  local_30 = local_20;
  fStack_2c = fStack_1c;
  fStack_28 = fStack_18;
  fStack_24 = *(float *)(unaff_ESI + 0x88); // max speed
  if ((flags & 0x200000) != 0) {
    fVar8 = *(float *)(*(int *)(unaff_ESI + 0x10) + 0x24); // some radius
    if (fVar8 <= fVar7) {
      local_40 = 0.0;
    }
    else {
      fVar8 = fVar7 / fVar8;
      fVar8 = fVar8 * fVar8 * fVar8 * fVar8;
      local_40 = (DAT_00e2b1a4 - (DAT_00e445ac - fVar8 * DAT_00e2b04c) * fVar8 * fVar8) * local_40;
    }
  }
  iVar3 = FUN_004bdae0(&local_30); // check if movement is valid (e.g., collision)
  if (((iVar3 != 0) && (iVar3 != 1)) ||
     (pfVar1 = (float *)(*(int *)(unaff_ESI + 0x10) + 0x28), result = 1,
     local_40 < *pfVar1 || local_40 == *pfVar1)) {
    result = 0;
  }
  if (outParams != (float *)0x0) {
    outParams[1] = local_40; // speed
    *outParams = fVar5 + fVar9 + fVar10; // dot product (direction alignment)
    outParams[2] = fVar7; // distance
  }
  return result;
}