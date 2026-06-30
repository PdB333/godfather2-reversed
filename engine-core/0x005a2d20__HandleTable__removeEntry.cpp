// FUNC_NAME: HandleTable::removeEntry
void HandleTable::removeEntry(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *in_EAX;
  
  puVar1 = (undefined4 *)*param_1;
  if ((undefined4 *)*in_EAX == puVar1) {
    if (puVar1 != (undefined4 *)0x0) {
      piVar2 = (int *)*puVar1;
      uVar3 = puVar1[1];
      if ((piVar2 != (int *)0x0) && (*piVar2 = *piVar2 + -1, *piVar2 == 0)) {
        FUN_005a2b80();
      }
      (*DAT_0119caf4)(puVar1);
      *param_1 = uVar3;
      return;
    }
  }
  else {
    do {
      puVar4 = puVar1;
      if (puVar4 == (undefined4 *)0x0) break;
      puVar1 = (undefined4 *)puVar4[1];
    } while ((undefined4 *)puVar4[1] != (undefined4 *)*in_EAX);
    puVar1 = (undefined4 *)puVar4[1];
    if (puVar1 != (undefined4 *)0x0) {
      puVar4[1] = puVar1[1];
      piVar2 = (int *)*puVar1;
      if ((piVar2 != (int *)0x0) && (*piVar2 = *piVar2 + -1, *piVar2 == 0)) {
        FUN_005a2b80();
      }
      (*DAT_0119caf4)(puVar1);
    }
  }
  return;
}