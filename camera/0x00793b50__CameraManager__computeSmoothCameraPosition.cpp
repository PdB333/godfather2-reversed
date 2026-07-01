// FUNC_NAME: CameraManager::computeSmoothCameraPosition
void __thiscall CameraManager::computeSmoothCameraPosition(int *this, undefined4 param_2, undefined4 param_3)
{
  float fVar1;
  undefined8 *puVar2;
  int iVar3;
  float fVar4;
  float local_54;
  float fStack_50;
  float local_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined1 local_20 [4];
  float fStack_1c;
  
  puVar2 = (undefined8 *)FUN_00471610(); // Get current camera position (likely a Vec2)
  local_4c = *(float *)(puVar2 + 1); // Y component
  local_54 = (float)*puVar2; // X component
  local_30 = local_54;
  fStack_50 = (float)((ulonglong)*puVar2 >> 0x20); // Extract high 32 bits as float (likely unused)
  local_2c = fStack_50;
  local_24 = 0.0;
  local_28 = local_4c;
  FUN_0056afa0(&local_30,&local_30); // Normalize or clamp direction vector
  (**(code **)(*this + 0x104))(local_20); // Get some transform matrix or orientation
  fVar1 = local_24;
  iVar3 = FUN_00471610(); // Get camera position again
  fVar4 = (float)this[0xcd] * DAT_00d6a0c4 - DAT_00d6a0c4; // Calculate interpolation factor from this+0x334 (0xcd*4)
  fStack_40 = fStack_34 * fVar4 + fVar1; // Lerp X
  fStack_3c = local_30 * fVar4 + *(float *)(iVar3 + 0x34); // Lerp Y
  fStack_38 = local_2c * fVar4 + fStack_1c; // Lerp Z
  fVar4 = DAT_00e44564 - fVar4; // Inverse interpolation factor
  local_4c = fStack_34 * fVar4 + fVar1; // Lerp X (other direction)
  fStack_48 = local_30 * fVar4 + *(float *)(iVar3 + 0x34); // Lerp Y (other direction)
  fStack_44 = local_2c * fVar4 + fStack_1c; // Lerp Z (other direction)
  FUN_004a08d0(param_2,param_3,&fStack_40,&local_4c); // Store final interpolated camera position
  return;
}