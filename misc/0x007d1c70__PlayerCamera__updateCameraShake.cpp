// FUNC_NAME: PlayerCamera::updateCameraShake
void __fastcall PlayerCamera::updateCameraShake(int this)
{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 local_4;
  
  iVar2 = FUN_007ab110(); // likely getCameraTransform or getCameraMatrix
  local_c = 0.0;
  local_4 = 0.0;
  fVar1 = *(float *)(this + 0x30); // +0x30: shakeDecayFactor or time
  uStack_8 = DAT_00e53028 - DAT_00e53030 * fVar1; // base offset minus decay
  iVar3 = FUN_00471610(); // likely getRandomStream or noise generator
  if ((*(byte *)(this + 0x84) & 1) == 0) { // +0x84: flags bit0 = shakeType (0=normal, 1=angular?)
    fVar4 = *(float *)(this + 0x80) * *(float *)(this + 0x7c); // +0x80: shakeIntensity, +0x7c: shakeMagnitude
  }
  else {
    fVar4 = *(float *)(this + 0x80); // angular shake uses intensity directly
    if (*(float *)(DAT_01223464 + 0x1694) <= fVar4 && fVar4 != *(float *)(DAT_01223464 + 0x1694)) {
      fVar4 = (fVar4 * _DAT_00e5302c + *(float *)(this + 0x7c)) - DAT_0112baa8 * fVar1; // combined with magnitude and decay
      goto LAB_007d1d2f;
    }
    fVar4 = *(float *)(this + 0x7c) * fVar4; // magnitude * intensity
  }
  fVar4 = fVar4 - DAT_0112baa8 * fVar1; // apply decay
LAB_007d1d2f:
  if (_DAT_00d577a0 < fVar4) { // threshold check
    local_c = *(float *)(iVar3 + 0x20) * fVar4; // random X component
    uStack_8 = *(float *)(iVar3 + 0x24) * fVar4 + uStack_8; // random Y component + base offset
    local_4 = *(float *)(iVar3 + 0x28) * fVar4; // random Z component
  }
  *(ulonglong *)(iVar2 + 100) = CONCAT44(uStack_8,local_c); // set camera offset (vec2 packed)
  *(float *)(iVar2 + 0x6c) = local_4; // set camera Z offset
  return;
}