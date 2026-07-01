// FUNC_NAME: CombatPerception::updateAlertState
void __fastcall CombatPerception::updateAlertState(int thisPtr)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  float10 fVar4;
  undefined4 uVar5;
  
  iVar1 = *(int *)(thisPtr + 0x58);  // +0x58: some component/manager pointer
  if ((*(int *)(thisPtr + 0x9c) != 0) && (*(int *)(thisPtr + 0x9c) != 0x48)) {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x1f30) + 8))();  // call on some object
    if (*(int *)(thisPtr + 0x9c) == 0) {  // +0x9c: entity/object pointer?
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(thisPtr + 0x9c) + -0x48);  // get base from offset 0x48
    }
    fVar4 = (float10)(**(code **)(*piVar3 + 0x21c))();  // virtual call: getSomeDistance?
    if (fVar4 < (float10)*(float *)(iVar1 + 0x2000)) {  // +0x2000: alert range threshold
      if (*(float *)(iVar1 + 0x1ffc) <= (float)fVar4) {  // +0x1ffc: mid alert range
        uVar5 = 0x25;  // ALERT_MEDIUM?
      }
      else {
        if ((float)fVar4 < *(float *)(iVar1 + 0x1ff8)) {  // +0x1ff8: low alert range
          return;  // no alert change
        }
        uVar5 = 0x24;  // ALERT_LOW?
      }
    }
    else {
      uVar5 = 0x26;  // ALERT_HIGH?
    }
    uVar5 = FUN_00799100(uVar5);  // convert alert enum to some value
    FUN_00444660(uVar2, uVar5);  // apply alert state via some function
  }
  return;
}