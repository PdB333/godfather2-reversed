// FUNC_NAME: Family::computeReputationPenaltyOrSomething
uint __thiscall Family::computeReputationPenaltyOrSomething(int this, uint param_2)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar2 = 0;
  uVar3 = 0;
  uVar4 = 0;
  piVar1 = (int *)FUN_00698c00(&param_2,param_2);
  if (*piVar1 == this + 4) {
    param_2 = param_2 & 0xffffff00;
  }
  else {
    // Some function at +0x20 in the pointed object
    FUN_004d3e20(*piVar1 + 0x20);
    param_2 = CONCAT31(param_2._1_3_,1);
  }
  if (iVar2 != 0) {
    (*(code *)0x0)(iVar2,iVar2,uVar3,uVar4);
  }
  return param_2 & 0xff;
}