// FUNC_NAME: VehicleAI::updateSteeringAndCollision
float * __thiscall VehicleAI::updateSteeringAndCollision(int this, undefined4 param_2, int *pTarget, int *pObstacle, int *pLeftSensor, int *pRightSensor)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  float local_c;
  float local_8;
  float local_4;
  
  iVar3 = *pTarget;
  if (iVar3 != 0) {
    iVar4 = pTarget[2]; // +0x8 - target position pointer
    iVar5 = *pObstacle;
    if (iVar5 != 0) {
      iVar1 = pObstacle[2]; // +0x8 - obstacle position pointer
      uVar2 = FUN_00860800(); // getFrameTime or similar
      FUN_008677a0(iVar3, iVar4, iVar5, iVar1, uVar2); // steerTowardsTarget
    }
  }
  iVar3 = *pLeftSensor;
  if (iVar3 == 0) {
    pfVar7 = (float *)0x0;
  }
  else {
    iVar4 = *pRightSensor;
    pfVar7 = (float *)pLeftSensor[2]; // +0x8 - left sensor position
    if (iVar4 != 0) {
      iVar5 = pRightSensor[2]; // +0x8 - right sensor position
      uVar2 = FUN_00860800(); // getFrameTime
      FUN_00868a60(iVar3, pfVar7, iVar4, iVar5, uVar2); // avoidObstacle
    }
  }
  if (*pRightSensor == 0) {
    pfVar6 = (float *)0x0;
  }
  else {
    pfVar6 = (float *)pRightSensor[2]; // +0x8 - right sensor position
  }
  if ((((pfVar7 != (float *)0x0) && (iVar3 != 0)) && (pfVar6 != (float *)0x0)) && (*pRightSensor != 0)) {
    local_c = *pfVar6 - *pfVar7; // dx = right - left
    local_8 = pfVar6[1] - pfVar7[1]; // dy
    local_4 = pfVar6[2] - pfVar7[2]; // dz
    FUN_0043a210(&local_c, &local_c); // normalize vector
    iVar3 = FUN_00471610(); // getVehicleTransform or similar
    iVar4 = FUN_00471610(); // getVehicleTransform
    iVar5 = FUN_00471610(); // getVehicleTransform
    pfVar6 = (float *)(iVar5 + 0x20); // +0x20 - forward vector component
    if (*(float *)(iVar4 + 0x24) * local_8 + *(float *)(iVar3 + 0x20) * local_c +
        *(float *)(iVar5 + 0x28) * local_4 < DAT_00d75cd8) { // dot product with forward
      pfVar6 = (float *)(*(uint *)(this + 0xfd4) & 0x7fffffff); // +0xfd4 - some flag
      *(undefined4 *)(this + 0xfd0) = 0; // +0xfd0 - clear steering input
      fVar8 = DAT_00d5eee4;
      if (pfVar6 == (float *)0x0) {
        fVar8 = DAT_00e44564;
      }
      *(float *)(this + 0xfc8) = DAT_00d75750 * 0.0 + fVar8; // +0xfc8 - set speed
    }
  }
  if (*(float *)(this + 0xf70) <= _DAT_00d577a0) { // +0xf70 - some threshold
    pfVar6 = (float *)FUN_008659a0(); // updateVehicleState
  }
  return pfVar6;
}