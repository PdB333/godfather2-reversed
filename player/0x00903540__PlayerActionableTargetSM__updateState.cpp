// FUNC_NAME: PlayerActionableTargetSM::updateState
void __fastcall PlayerActionableTargetSM::updateState(int thisPtr)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *unaff_EDI;
  uint uVar4;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if ((*(uint *)(thisPtr + 0xa0) >> 1 & 1) == 0) {
    piVar3 = (int *)FUN_00446100(thisPtr + 0x50,0);
    if (piVar3 != (int *)0x0) {
      uVar4 = 0x420f378a;
      local_14 = 0;
      cVar1 = (**(code **)(*piVar3 + 0x10))(0x420f378a,&local_14);
      if ((cVar1 != '\0') && (unaff_EDI != (int *)0x0)) {
        local_14 = 0xbeefbeef;
        uStack_10 = 0xeac15a55;
        uStack_c = 0x91100911;
        (**(code **)(*unaff_EDI + 0x158))(&stack0xffffffe8);
        piVar3 = (int *)FUN_00446100(&stack0xffffffe8,0);
      }
      if (piVar3 != (int *)0x0) {
        cVar1 = (**(code **)(*piVar3 + 0x10))(0x38523fc3,&stack0xffffffe4);
        FUN_0044b210(-(uint)(cVar1 != '\0') & uVar4);
        if ((*(int *)(thisPtr + 0x60) != 0) && (*(int *)(thisPtr + 0x60) != 0x48)) {
          *(uint *)(thisPtr + 0xa0) = *(uint *)(thisPtr + 0xa0) | 2;
          if (*(int *)(thisPtr + 0x80) != 0) {
            FUN_00440590(thisPtr + 0x80,0,*(undefined4 *)(thisPtr + 0x90),0,0);
            if ((0 < *(int *)(thisPtr + 0x94)) &&
               (iVar2 = *(int *)(thisPtr + 0x94) + -1, *(int *)(thisPtr + 0x94) = iVar2, iVar2 < 1))
            {
              FUN_004088c0(thisPtr + 0x3c);
            }
          }
        }
      }
    }
  }
  else if ((*(int *)(thisPtr + 0x60) == 0) || (*(int *)(thisPtr + 0x60) == 0x48)) {
    *(uint *)(thisPtr + 0xa0) = *(uint *)(thisPtr + 0xa0) & 0xfffffffd;
    if (*(int *)(thisPtr + 0x88) != 0) {
      FUN_00440590(thisPtr + 0x88,0,*(undefined4 *)(thisPtr + 0x90),0);
      if ((0 < *(int *)(thisPtr + 0x94)) &&
         (iVar2 = *(int *)(thisPtr + 0x94) + -1, *(int *)(thisPtr + 0x94) = iVar2, iVar2 < 1)) {
        FUN_004088c0();
        return;
      }
    }
  }
  return;
}