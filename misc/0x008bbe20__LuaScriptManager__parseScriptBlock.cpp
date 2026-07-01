// FUNC_NAME: LuaScriptManager::parseScriptBlock
void __thiscall parseScriptBlock(int this, undefined4 scriptData)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_008bb320(scriptData);
  FUN_0043aff0(scriptData,0x3fb43b57);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      iVar3 = this + 0x290;  // +0x290: script state pointer
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 1:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x2a0) = *(undefined4 *)(iVar3 + 8);  // +0x2a0: script integer value
      break;
    case 2:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x2a4) = *(undefined4 *)(iVar3 + 8);  // +0x2a4: script float value
      break;
    case 3:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x2a8) = *(undefined4 *)(iVar3 + 8);  // +0x2a8: script string pointer
      break;
    case 4:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x2ac) = *(undefined4 *)(iVar3 + 8);  // +0x2ac: script boolean
      break;
    case 5:
      iVar3 = FUN_0043b210();
      *(undefined1 *)(this + 0x2b0) = *(undefined1 *)(iVar3 + 8);  // +0x2b0: script byte
      break;
    case 6:
      iVar3 = FUN_0043b210();
      *(undefined2 *)(this + 0x2b2) = *(undefined2 *)(iVar3 + 8);  // +0x2b2: script short
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}