// FUNC_NAME: ScriptParser::parseBlock
void ScriptParser::parseBlock(int param_1)

{
  int iVar1;
  code *pcVar2;
  int in_EAX;
  undefined4 uVar3;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = *(int *)(in_EAX + 0x1c);
  local_4 = 0;
  local_10 = 0xffffffff;
  local_c = *(undefined4 *)(iVar1 + 0x34);
  local_8 = 0;
  local_14 = *(undefined4 *)(iVar1 + 0x14);
  *(undefined4 **)(iVar1 + 0x14) = &local_14;
  *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4);
  if (*(int *)(in_EAX + 0x14) == 0x11f) {
    uVar3 = FUN_00639c70(in_EAX + 0x10);
    *(undefined4 *)(in_EAX + 0xc) = uVar3;
  }
  else {
    *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EAX + 0x14);
    *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
    *(undefined4 *)(in_EAX + 0x14) = 0x11f;
  }
  uVar3 = FUN_0063dd40();
  iVar1 = *(int *)(in_EAX + 0xc);
  if (iVar1 == 0x2c) {
LAB_00640cfb:
    FUN_006409b0(uVar3);
  }
  else {
    if (iVar1 != 0x3d) {
      if (iVar1 == 0x10b) goto LAB_00640cfb;
      FUN_00638b80("`=\\' or `in\\' expected");
    }
    FUN_00640720(param_1);
  }
  if (*(int *)(in_EAX + 0xc) != 0x106) {
    if (param_1 == *(int *)(in_EAX + 4)) {
      uVar3 = FUN_00636c00("`%s\\' expected",PTR_DAT_00e2a8d4);
      FUN_00638b80(uVar3);
    }
    uVar3 = FUN_00636c00("`%s\\' expected (to close `%s\\' at line %d)",PTR_DAT_00e2a8d4,
                         PTR_DAT_00e2a8dc,param_1);
    FUN_00638b80(uVar3);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4);
  if (*(int *)(in_EAX + 0x14) != 0x11f) {
    uVar3 = *(undefined4 *)(in_EAX + 0x14);
    *(undefined4 *)(in_EAX + 0x14) = 0x11f;
    *(undefined4 *)(in_EAX + 0xc) = uVar3;
    *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
    FUN_0063e400();
    return;
  }
  uVar3 = FUN_00639c70(in_EAX + 0x10);
  *(undefined4 *)(in_EAX + 0xc) = uVar3;
  FUN_0063e400();
  return;
}