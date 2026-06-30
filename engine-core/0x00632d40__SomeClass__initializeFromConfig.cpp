// FUNC_NAME: SomeClass::initializeFromConfig
void __fastcall SomeClass::initializeFromConfig(int param_1)
{
  int iVar1;
  int in_EAX;
  undefined *puVar2;
  
  iVar1 = *(int *)(in_EAX + 4);
  if (*(char *)(iVar1 + 6) == '\0') {
    // +0x10: some pointer field
    *(int *)(param_1 + 0x10) = *(int *)(*(int *)(iVar1 + 0xc) + 0x20) + 0x10;
    iVar1 = *(int *)(*(int *)(iVar1 + 0xc) + 0x3c);
    // +0x1c: some integer field
    *(int *)(param_1 + 0x1c) = iVar1;
    puVar2 = &DAT_00e41eb8;
    if (iVar1 != 0) {
      puVar2 = &DAT_00e37bec;
    }
    // +0xc: some pointer field
    *(undefined **)(param_1 + 0xc) = puVar2;
  }
  else {
    *(undefined **)(param_1 + 0x10) = &DAT_00e41eac;
    *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
    *(undefined **)(param_1 + 0xc) = &DAT_00e41eb4;
  }
  // Initialize a sub-object at offset +0x20
  FUN_00636c20(param_1 + 0x20, *(undefined4 *)(param_1 + 0x10));
  return;
}