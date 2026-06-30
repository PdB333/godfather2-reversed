// FUNC_NAME: SomeClass::processQueueOrList
undefined1 FUN_005a20d0(undefined4 param_1, int *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_25;
  int local_24;
  int *local_20 [3];
  undefined1 *puStack_14;
  undefined1 auStack_10 [16];
  
  local_25 = 1;
  local_24 = 0;
  if (0 < *(int *)(param_2[10] + 0x28)) {
    do {
      uVar2 = FUN_005a0980();
      FUN_005a1eb0(local_20,uVar2);
      piVar1 = local_20[0];
      if ((local_20[0] == (int *)0x0) || (local_20[0][8] != 4)) {
        piVar3 = (int *)0x0;
        if (local_20[0] != (int *)0x0) goto LAB_005a2136;
      }
      else {
        *local_20[0] = *local_20[0] + 1;
        piVar3 = local_20[0];
LAB_005a2136:
        *local_20[0] = *local_20[0] + -1;
        if (*local_20[0] == 0) {
          FUN_005a1b40();
          (*DAT_0119caf8)(piVar1,0x30);
        }
      }
      if ((piVar3 != (int *)0x0) && (*piVar3 = *piVar3 + -1, *piVar3 == 0)) {
        FUN_005a1b40();
        (*DAT_0119caf8)(piVar3,0x30);
      }
      if ((puStack_14 != auStack_10) && (puStack_14 != (undefined1 *)0x0)) {
        (*DAT_0119caf4)(puStack_14);
      }
      if (piVar3 == (int *)0x0) {
        local_25 = 0;
        break;
      }
      local_24 = local_24 + 1;
    } while (local_24 < *(int *)(param_2[10] + 0x28));
  }
  *param_2 = *param_2 + -1;
  if (*param_2 == 0) {
    FUN_005a1b40();
    (*DAT_0119caf8)(param_2,0x30);
  }
  return local_25;
}