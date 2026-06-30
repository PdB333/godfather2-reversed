// FUNC_NAME: CameraManager::applyCameraShake
void CameraManager::applyCameraShake(int param_1, float *param_2, undefined4 *param_3)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float fStack_5c;
  float fStack_58;
  undefined1 local_50 [76];
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar3 = param_2[2];
  fVar4 = *(float *)(param_1 + 0x104); // +0x104: shakeIntensity or shakeFactor
  local_70 = *param_3;
  local_6c = param_3[1];
  local_68 = param_3[2];
  local_64 = _DAT_00d5780c; // global constant (likely identity quaternion or zero vector)
  FUN_00471610(); // likely some math utility (e.g., matrix/vector operations)
  FUN_006e3b00(); // likely another camera shake helper
  FUN_0056b420(local_50, &local_70, &local_60); // likely quaternion/rotation multiplication
  fVar6 = (fStack_5c - fVar4 * fVar2) * DAT_00e514ac; // DAT_00e514ac: global scale factor
  fVar7 = (fStack_58 - fVar4 * fVar3) * DAT_00e514ac;
  fVar5 = *(float *)(param_1 + 0x108); // +0x108: shakeDamping or shakeMultiplier
  *param_2 = fVar5 * ((local_60 - fVar4 * fVar1) * DAT_00e514ac + fVar4 * fVar1);
  param_2[1] = fVar5 * (fVar6 + fVar4 * fVar2);
  param_2[2] = fVar5 * (fVar7 + fVar4 * fVar3);
  return;
}