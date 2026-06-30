// FUNC_NAME: ScriptEngine::parseConstructor
void ScriptEngine::parseConstructor(int param_1)

{
  code *pcVar1;
  int in_EAX;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_24;
  undefined4 uStack_20;
  
  iVar7 = *(int *)(in_EAX + 0x1c); // +0x1c: current token stream
  uVar6 = *(undefined4 *)(iVar7 + 0x24); // +0x24: saved position
  if (*(int *)(in_EAX + 0xc) == 0x116) { // token type: constructor keyword
    iVar3 = *(int *)(param_1 + 0x18); // +0x18: constructor count
    if (0x7ffffffd < iVar3) {
      uVar2 = FUN_00636c00("too many %s (limit=%d)","items in a constructor",0x7ffffffd);
      iVar3 = FUN_00638b80(uVar2);
      iVar7 = in_EAX;
    }
    *(int *)(param_1 + 0x18) = iVar3 + 1;
    uStack_34 = FUN_0063dd40(); // allocate new object
    uStack_38 = 4;
    uStack_2c = FUN_00642970(*(undefined4 *)(in_EAX + 0x1c),&uStack_38); // read token
    uStack_24 = 0xffffffff;
    uStack_20 = 0xffffffff;
    local_30 = 4;
  }
  else {
    FUN_0063e860(); // parse expression
  }
  if (*(int *)(in_EAX + 0xc) == 0x3d) { // token type: assignment
    *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(in_EAX + 4); // copy value
    if (*(int *)(in_EAX + 0x14) == 0x11f) { // token type: identifier
      uVar2 = FUN_00639c70(in_EAX + 0x10); // resolve identifier
      *(undefined4 *)(in_EAX + 0xc) = uVar2;
    }
    else {
      *(undefined4 *)(in_EAX + 0xc) = *(undefined4 *)(in_EAX + 0x14);
      *(undefined4 *)(in_EAX + 0x10) = *(undefined4 *)(in_EAX + 0x18);
      *(undefined4 *)(in_EAX + 0x14) = 0x11f;
    }
    FUN_00642fc0(); // push stack
    FUN_0063fad0(); // evaluate expression
    uVar4 = FUN_00642fc0(); // pop stack
    uVar5 = FUN_00642fc0(); // pop stack
    FUN_006438e0(((*(int *)(*(int *)(param_1 + 0x14) + 4) << 9 | uVar5) << 9 | uVar4) << 6 | 9,
                 *(undefined4 *)(*(int *)(iVar7 + 0xc) + 8)); // emit bytecode
    *(undefined4 *)(iVar7 + 0x24) = uVar6; // restore position
    return;
  }
  uVar6 = FUN_00636c00(&DAT_00e4242c,0x3d);
  uVar6 = FUN_00636c00("`%s\\' expected",uVar6);
  FUN_00638b80(uVar6);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}