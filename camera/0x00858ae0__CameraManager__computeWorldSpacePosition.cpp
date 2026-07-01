// FUNC_NAME: CameraManager::computeWorldSpacePosition
void CameraManager::computeWorldSpacePosition(float *localPos, undefined4 *worldPosOut)

{
  undefined8 uVar1;
  int iVar2;
  float local_e8;
  float local_e4;
  float local_e0;
  undefined8 local_dc;
  float local_d4;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float local_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined1 local_90 [12];
  undefined4 local_84;
  undefined4 local_74;
  undefined4 local_64;
  undefined4 local_54;
  undefined1 local_50 [12];
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_44 = 0;
  local_34 = 0;
  local_24 = 0;
  local_d0 = _DAT_00d5780c; // identity quaternion w=1
  uStack_cc = 0;
  uStack_c8 = 0;
  uStack_c4 = 0;
  local_c0 = 0;
  uStack_bc = _DAT_00d5780c;
  uStack_b8 = 0;
  uStack_b4 = 0;
  local_b0 = 0;
  uStack_ac = 0;
  uStack_a8 = _DAT_00d5780c;
  uStack_a4 = 0;
  uStack_94 = _DAT_00d5780c;
  local_a0 = *param_1 + 0.0;
  fStack_9c = param_1[1] + 0.0;
  fStack_98 = param_1[2] + 0.0;
  local_14 = _DAT_00d5780c;
  iVar2 = FUN_00471610(); // getTimeManager
  uVar1 = *(undefined8 *)(iVar2 + 0x30); // timeManager->currentTime (64-bit)
  local_d4 = *(float *)(iVar2 + 0x38); // timeManager->deltaTime
  local_dc._0_4_ = (float)uVar1;
  local_a0 = local_a0 + (DAT_00e44564 - (float)local_dc); // adjust for time offset
  local_dc._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
  fStack_9c = fStack_9c + (DAT_00e44564 - local_dc._4_4_);
  fStack_98 = fStack_98 + (DAT_00e44564 - local_d4);
  local_84 = 0;
  local_74 = 0;
  local_64 = 0;
  local_54 = _DAT_00d5780c;
  local_dc = uVar1;
  FUN_00470f80(local_90); // getCameraTransform
  FUN_0056c180(local_90,&local_e4,&local_e8,&local_e0); // extractEulerAngles
  local_e8 = -local_e8;
  local_e4 = -local_e4;
  local_e0 = -local_e0;
  FUN_0056b8a0(local_e4,local_e8,local_e0,local_90); // buildRotationMatrix
  FUN_008588b0(local_50); // transformPoint
  *param_2 = local_20;
  param_2[1] = local_1c;
  param_2[2] = local_18;
  return;
}