// Xbox PDB: EARS::Framework::Lua::MessageReceiver::LuaNew
// FUNC_NAME: MessageReceiver::luaNew
undefined4 MessageReceiver::luaNew(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float fVar5;
  undefined4 local_14;
  int iStack_10;
  undefined4 uStack_c;
  
  piVar4 = *(int **)(param_1 + 0xc);
  if ((piVar4 < *(int **)(param_1 + 8)) && (piVar4 != (int *)0x0)) {
    if (*piVar4 != 3) {
      if (*piVar4 == 4) {
        iVar3 = FUN_00636850(&local_14);
        if (iVar3 != 0) goto LAB_004ce88a;
      }
      goto LAB_004ce87e;
    }
  }
  else {
LAB_004ce87e:
    FUN_00627bd0("MessageReceiverNew expects an integer as its argument\n");
  }
LAB_004ce88a:
  piVar4 = *(int **)(param_1 + 0xc);
  if ((piVar4 < *(int **)(param_1 + 8)) && (piVar4 != (int *)0x0)) {
    if (*piVar4 == 3) {
LAB_004ce8d1:
      fVar5 = (float)piVar4[1];
      goto LAB_004ce8db;
    }
    if (*piVar4 == 4) {
      iVar3 = FUN_00636850(&local_14);
      if (iVar3 != 0) {
        iStack_10 = 3;
        uStack_c = local_14;
        piVar4 = &iStack_10;
        goto LAB_004ce8d1;
      }
    }
  }
  fVar5 = 0.0;
LAB_004ce8db:
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24)) {
    FUN_00627360();
  }
  iVar3 = FUN_00638a40(0x34);
  puVar1 = *(undefined4 **)(param_1 + 8);
  *puVar1 = 7;
  puVar1[1] = iVar3;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 8;
  if (iVar3 == -0x10) {
    FUN_00627bd0("MessageReceiver::LuaNew: out of memory");
  }
  FUN_004ce090(param_1,(int)fVar5);
  iVar3 = FUN_00627c90(param_1,"MessageReceiver");
  if (iVar3 != 0) {
    FUN_004aeb70(&PTR_s___index_00e36ab0);
  }
  iVar2 = *(int *)(param_1 + 8);
  iVar3 = iVar2 + -8;
  if (*(int *)(iVar2 + -8) == 0) {
    iVar3 = *(int *)(param_1 + 0x10) + 0x34;
  }
  if ((*(int *)(iVar2 + -0x10) == 5) || (*(int *)(iVar2 + -0x10) == 7)) {
    *(undefined4 *)(*(int *)(iVar2 + -0xc) + 8) = *(undefined4 *)(iVar3 + 4);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -8;
  return 1;
}