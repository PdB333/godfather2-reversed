// FUNC_NAME: PlayerSM::checkCondition
uint __thiscall PlayerSM::checkCondition(int thisPtr, int param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
  char cVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  float10 fVar7;
  
  bVar4 = 0;
  switch(param4) {
  case 10: // Condition: IsNotInCar
    uVar5 = FUN_006252d0(); // likely getPlayerIndex or similar
    if ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94) & uVar5) != 0) {
      return 1;
    }
    break;
  case 0xb: // Condition: IsInCar
    uVar5 = FUN_006252d0();
    if ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94) & uVar5) == 0) {
      return 1;
    }
    break;
  case 0xc: // Condition: IsCurrentWeaponType
    cVar1 = *(char *)(*(int *)(thisPtr + 0x58) + 0x1b8c);
    cVar3 = FUN_006252d0();
    if (cVar1 == cVar3) {
      return 1;
    }
    break;
  case 0xd: // Condition: IsHealthBelow
    fVar2 = (float)param2;
    if (param2 < 0) {
      fVar2 = fVar2 + DAT_00e44578; // float constant for negative handling
    }
    if (((*(float *)(thisPtr + 0x60) < fVar2 * DAT_00d5efb8) || // health check
        ((*(byte *)(*(int *)(thisPtr + 0x58) + 0x1f5a) & 1) != 0)) || // some flag
       ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94) >> 0xd & 1) != 0)) { // another flag
      return 1;
    }
    break;
  case 0xe: // Condition: IsHealthAbove
    fVar2 = (float)param2;
    if (param2 < 0) {
      fVar2 = fVar2 + DAT_00e44578;
    }
    if (*(float *)(thisPtr + 0x68) < fVar2 * DAT_00d5efb8) { // health check
      return 1;
    }
    break;
  case 0xf: // Condition: CanEnterCar
    uVar5 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94);
    if ((uVar5 >> 0xf & 1) != 0) { // already in car
      return 0;
    }
    if ((uVar5 >> 3 & 1) == 0) { // not in combat
      return 1;
    }
    fVar2 = (float)param2;
    if (param2 < 0) {
      fVar2 = fVar2 + DAT_00e44578;
    }
    if ((*(float *)(thisPtr + 100) < fVar2 * DAT_00d5efb8) || // health check
       ((*(byte *)(*(int *)(thisPtr + 0x58) + 0x1f5a) & 1) != 0)) { // some flag
      return 1;
    }
    break;
  case 0x10: // Condition: CanExitCar
    uVar5 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94);
    if ((uVar5 >> 0xf & 1) == 0) { // not in car
      if ((uVar5 >> 3 & 1) != 0) { // in combat
        fVar2 = (float)param2;
        if (param2 < 0) {
          fVar2 = fVar2 + DAT_00e44578;
        }
        if (fVar2 * DAT_00d5efb8 <= *(float *)(thisPtr + 100)) { // health check
          return 0;
        }
      }
      iVar6 = (**(code **)(**(int **)(thisPtr + 0x5c) + 0x34))(); // get some object
      if (((*(int *)(iVar6 + 0x30) == 1) && // some state check
          (fVar7 = (float10)FUN_00733f60(), fVar7 < (float10)_DAT_00d5ca1c)) && // time check
         (2 < *(uint *)(*(int *)(thisPtr + 0x58) + 0x1ed0))) { // passenger count
        return 1;
      }
    }
    return 0;
  case 0x11: // Condition: IsInCarAndNotDriver
    uVar5 = *(uint *)(*(int *)(thisPtr + 0x58) + 0x1b94);
    if ((uVar5 >> 0xf & 1) == 0) { // not in car
      return uVar5 >> 0xd & 1; // return passenger flag
    }
    break;
  default:
    bVar4 = FUN_004ac640(param2,param3,param4,param5); // fallback to generic condition check
  }
  return (uint)bVar4;
}