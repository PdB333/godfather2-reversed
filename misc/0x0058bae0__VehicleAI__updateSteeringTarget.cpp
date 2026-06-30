// FUNC_NAME: VehicleAI::updateSteeringTarget
undefined4 VehicleAI::updateSteeringTarget(undefined4 this, int vehicleData, int *waypointArray, float targetX, float targetZ, uint flags, undefined4 param_7)
{
  short sVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  uint uVar5;
  
  piVar3 = waypointArray;
  iVar2 = vehicleData;
  if (*(char *)(vehicleData + 1) == '\0') {
    return 0;
  }
  sVar1 = *(short *)(vehicleData + 2);
  if ((uint)waypointArray[1] <= (uint)(int)sVar1) {
    vehicleData = 0;
    FUN_00591c00(&vehicleData);
  }
  uVar5 = (uint)*(short *)(iVar2 + 2);
  targetX = (*(float *)(*piVar3 + sVar1 * 4) - DAT_00e2b1a4) - targetX;
  if ((uint)piVar3[1] <= uVar5) {
    vehicleData = 0;
    FUN_00591c00(&vehicleData);
  }
  uVar4 = FUN_0058afb0(this, iVar2, piVar3, targetX,
                       (*(float *)(*piVar3 + uVar5 * 4) - DAT_00e2b1a4) - targetZ, flags ^ 2,
                       param_7);
  return uVar4;
}