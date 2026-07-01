// FUNC_NAME: PlayerF2FSM::processF2FInteractions
void __fastcall PlayerF2FSM::processF2FInteractions(int *thisPtr)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int unaff_ESI;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  piVar4 = thisPtr;
  if ((thisPtr != (int *)0x0) && (piVar2 = (int *)FUN_0043b870(DAT_01131018), piVar2 != (int *)0x0))
  {
    iVar3 = (**(code **)(*piVar2 + 0x34))();
    if ((*(int *)(iVar3 + 0xc) == 0) ||
       (piVar4 = (int *)(*(int *)(iVar3 + 0xc) + -0x48), piVar4 == (int *)0x0)) {
      piVar4 = (int *)(**(code **)(*thisPtr + 0x1e4))();
    }
  }
  local_14 = 0;
  local_18 = 0;
  cVar1 = (**(code **)(*thisPtr + 0x1cc))(&local_18);
  while (cVar1 != '\0') {
    piVar2 = (int *)(**(code **)(*thisPtr + 500))(&uStack_1c);
    if (piVar2 != (int *)0x0) {
      cVar1 = (**(code **)(*piVar2 + 0x10))(0x369ac561,&stack0xffffffdc);
      if ((cVar1 != '\0') && (unaff_ESI != 0)) {
        if ((*(uint *)(unaff_ESI + 0x1f5c) >> 3 & 1) == 0) {
          FUN_00876bb0(unaff_ESI,piVar4);
        }
        FUN_004088c0(piVar2 + 0xf);
      }
      uStack_1c = 0;
      uStack_20 = 0;
      (**(code **)(*thisPtr + 0x204))(piVar2,&uStack_20);
      FUN_007ff8a0(0);
      FUN_007f6420(4);
    }
    cVar1 = (**(code **)(*thisPtr + 0x1d0))(&uStack_20,&uStack_20);
  }
  return;
}