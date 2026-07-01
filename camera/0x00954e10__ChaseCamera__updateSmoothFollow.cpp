// FUNC_NAME: ChaseCamera::updateSmoothFollow
void __fastcall ChaseCamera::updateSmoothFollow(int this)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  
  iVar1 = *(int *)(this + 0x6c); // +0x6c: pointer to camera state struct
  uVar2 = *(undefined4 *)(iVar1 + 0xdc); // +0xdc: current target orientation quaternion
  fVar4 = *(float *)(iVar1 + 0x120); // +0x120: target position X
  fVar5 = *(float *)(iVar1 + 0x124); // +0x124: target position Y
  fVar6 = *(float *)(iVar1 + 0x128); // +0x128: target position Z
  fVar11 = fVar4 - *(float *)(iVar1 + 0xd0); // +0xd0: current position X
  fVar13 = fVar5 - *(float *)(iVar1 + 0xd4); // +0xd4: current position Y
  fVar14 = fVar6 - *(float *)(iVar1 + 0xd8); // +0xd8: current position Z
  fVar9 = fVar13 * fVar13 + fVar14 * fVar14 + fVar11 * fVar11; // squared distance to target
  fVar10 = SQRT(fVar9); // distance to target
  if (DAT_00e57424 <= fVar10) { // if distance > minThreshold
    uVar8 = FUN_00494d10(); // get current game time
    iVar1 = *(int *)(this + 0x6c);
    if (*(uint *)(iVar1 + 0x130) < uVar8) { // if next update time < current time
      if (*(int *)(iVar1 + 0x110) == 3) { // state == 3 (snap to target)
        uVar2 = *(undefined4 *)(iVar1 + 0xdc);
        *(undefined4 *)(iVar1 + 0xd0) = *(undefined4 *)(iVar1 + 0x120); // snap position to target
        *(undefined4 *)(iVar1 + 0xd4) = *(undefined4 *)(iVar1 + 0x124);
        *(undefined4 *)(iVar1 + 0xd8) = *(undefined4 *)(iVar1 + 0x128);
        *(undefined4 *)(iVar1 + 0xdc) = *(undefined4 *)(iVar1 + 300); // +0x12c: target orientation
        *(undefined4 *)(iVar1 + 0xdc) = uVar2;
        FUN_00954d30(); // finalize camera update
        return;
      }
      fVar12 = fVar10 / *(float *)(iVar1 + 0x160); // +0x160: speed factor
      if (0.0 < fVar12) {
        if (_DAT_00d5780c <= fVar12) {
          fVar12 = _DAT_00d5780c; // clamp to max speed
        }
      }
      else {
        fVar12 = 0.0;
      }
      if (fVar9 <= DAT_00d5f2b4) {
        fVar9 = 0.0;
      }
      else {
        fVar9 = _DAT_00d5780c / SQRT(fVar9); // normalize direction
      }
      fVar10 = DAT_00e44564 -
               (fVar10 - ((*(float *)(iVar1 + 0x15c) - *(float *)(iVar1 + 0x158)) * fVar12 +
                         *(float *)(iVar1 + 0x158))); // +0x158: min distance, +0x15c: max distance
      uVar3 = *(undefined4 *)(iVar1 + 0xdc);
      *(float *)(iVar1 + 0xd0) = fVar10 * fVar9 * fVar11 + fVar4; // interpolate position
      *(float *)(iVar1 + 0xd4) = fVar10 * fVar9 * fVar13 + fVar5;
      *(float *)(iVar1 + 0xd8) = fVar10 * fVar9 * fVar14 + fVar6;
      *(undefined4 *)(iVar1 + 0xdc) = uVar2;
      *(undefined4 *)(iVar1 + 0xdc) = uVar3;
    }
    return;
  }
  if (*(int *)(iVar1 + 0x110) == 2) { // state == 2 (approaching target)
    *(undefined4 *)(iVar1 + 0x110) = 1; // transition to state 1 (following)
    *(undefined4 *)(iVar1 + 0x120) = *(undefined4 *)(iVar1 + 0x140); // +0x140: new target position
    *(undefined4 *)(iVar1 + 0x124) = *(undefined4 *)(iVar1 + 0x144);
    *(undefined4 *)(iVar1 + 0x128) = *(undefined4 *)(iVar1 + 0x148);
    *(undefined4 *)(iVar1 + 300) = *(undefined4 *)(iVar1 + 0x14c); // +0x14c: new target orientation
    iVar7 = FUN_00494d10(); // get current time
    *(undefined4 *)(iVar1 + 0x15c) = *(undefined4 *)(iVar1 + 0x154); // +0x154: new max distance
    *(int *)(iVar1 + 0x130) = iVar7 + *(int *)(iVar1 + 0x150); // +0x150: duration until next update
    return;
  }
  *(undefined4 *)(iVar1 + 0x110) = 0; // state = 0 (idle)
  return;
}