// FUNC_NAME: PlayerCarryInteraction::performDropCarryAction
void __thiscall PlayerCarryInteraction::performDropCarryAction(int thisPtr, int *carryData)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  
  piVar1 = carryData;
  if (((DAT_00d5ef84 < *(float *)(thisPtr + 500)) && (carryData != (int *)0x0)) &&
     (cVar2 = (**(code **)(*carryData + 0x78))(), cVar2 != '\0')) {
    // Check if carry data is valid and perform drop action
    FUN_0084dd20(); // likely some preprocessing or state validation
    if (**(int **)(DAT_012233a0 + 4) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // offset calculation
    }
    FUN_0044b210(thisPtr); // release or cleanup player carry state
    FUN_0044b210(iVar3); // release or cleanup related entity state
    FUN_00471610(); // likely network sync
    FUN_00471610(); // likely network sync repeated
    carryData = (int *)0x0;
    (**(code **)(*piVar1 + 0x10))(0x55859efa,&carryData); // virtual call on carry interface
    FUN_00408bb0(&DAT_0112dd94,piVar1 + 0xf,&stack0xffffffb0,0); // log or debug output
    FUN_0070aaf0(); // update animation or state machine
  }
  return;
}