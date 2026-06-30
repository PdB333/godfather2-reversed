// FUNC_NAME: SomeManager::removeOrReleaseItem
undefined1 __fastcall SomeManager::removeOrReleaseItem(undefined4 param_1, int param_2)
{
  int *piVar1;
  char cVar2;
  undefined1 uVar3;
  int in_EAX;
  int *piVar4;
  uint uVar5;
  
  uVar3 = 0;
  uVar5 = 0;
  if (*(uint *)(in_EAX + 0x6018) != 0) {
    piVar4 = *(int **)(in_EAX + 0x6014);
    while ((piVar1 = (int *)*piVar4, piVar1 == (int *)0x0 || (*piVar1 != param_2))) {
      uVar5 = uVar5 + 1;
      piVar4 = piVar4 + 1;
      if (*(uint *)(in_EAX + 0x6018) <= uVar5) {
        return 0;
      }
    }
    cVar2 = FUN_005f03c0(DAT_01223514);
    if (cVar2 != '\0') {
      uVar3 = (**(code **)(*DAT_01223510 + 0x14))(piVar1);
      FUN_005e6d20();
      FUN_009c8eb0(piVar1);
    }
  }
  return uVar3;
}