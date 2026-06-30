// FUNC_NAME: SomeClass::initializeOrReset
void SomeClass::initializeOrReset(int param_1)
{
  undefined1 *puVar1;
  
  *(undefined1 *)(param_1 + 0x68) = 0;
  puVar1 = *(undefined1 **)(param_1 + 4);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = &DAT_0120546e;
  }
  FUN_004089b0(param_1 + 0x44,puVar1);
  puVar1 = *(undefined1 **)(param_1 + 0x14);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = &DAT_0120546e;
  }
  FUN_004089b0(param_1 + 0x4c,puVar1);
  if (*(int *)(param_1 + 0x28) != 0) {
    puVar1 = *(undefined1 **)(param_1 + 0x24);
    if (puVar1 == (undefined1 *)0x0) {
      puVar1 = &DAT_0120546e;
    }
    FUN_004089b0(param_1 + 0x54,puVar1);
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    puVar1 = *(undefined1 **)(param_1 + 0x34);
    if (puVar1 == (undefined1 *)0x0) {
      puVar1 = &DAT_0120546e;
    }
    FUN_004089b0(param_1 + 0x5c,puVar1);
  }
  return;
}