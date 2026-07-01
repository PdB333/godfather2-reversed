// FUNC_NAME: VehiclePhysics::computeEngineForce
float __fastcall VehiclePhysics::computeEngineForce(int this)
{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float fVar6;
  double dVar7;
  float fVar8;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float local_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float local_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float local_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  undefined4 local_14;
  
  fStack_44 = 0.0;
  fStack_34 = 0.0;
  fStack_24 = 0.0;
  local_14 = _DAT_00d5780c;
  // Get gear ratio from transmission data at this+0x58
  FUN_00425060(&local_6c, *(undefined4 *)(&DAT_00002494 + *(int *)(this + 0x58)));
  // Convert gear ratio to rotation matrix
  FUN_0056b8a0(local_68, local_6c, local_64, &local_50);
  // Get random value for engine torque variation
  fVar5 = (float10)FUN_0079eb90(0, 0);
  dVar7 = (double)(float)fVar5;
  FUN_00b99fcb();
  local_60 = (float)dVar7;
  dVar7 = (double)(float)fVar5;
  FUN_00b99e20();
  fVar6 = (float)dVar7;
  // Apply torque curve based on RPM
  fStack_4c = local_60 * fStack_4c;
  fStack_48 = local_60 * fStack_48;
  fVar8 = local_60 * fStack_44;
  local_60 = local_40 * 0.0 + local_60 * local_50 + fVar6 * local_30;
  fStack_5c = fStack_3c * 0.0 + fStack_4c + fVar6 * fStack_2c;
  fStack_58 = fStack_38 * 0.0 + fStack_48 + fVar6 * fStack_28;
  fStack_54 = fStack_34 * 0.0 + fVar8 + fVar6 * fStack_24;
  // Get wheel contact info
  iVar2 = FUN_00471610();
  iVar3 = FUN_00471610();
  iVar4 = FUN_00471610();
  // Compute torque contribution from each wheel
  fVar6 = *(float *)(iVar3 + 0x24) * fStack_5c;
  fVar1 = *(float *)(iVar2 + 0x20) * local_60;
  fVar8 = *(float *)(iVar4 + 0x28) * fStack_58;
  // Apply throttle input and clamp
  fVar5 = (float10)FUN_0079eb40(0, 0);
  fVar5 = fVar5 * (float10)(fVar8 + fVar1 + fVar6);
  if (fVar5 < (float10)*(float *)(DAT_01223464 + 0x1694)) {
    fVar5 = (float10)0.0;
  }
  return fVar5;
}