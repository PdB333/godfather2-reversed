// FUNC_NAME: LuaScript::parseAndExecute
void __thiscall LuaScript::parseAndExecute(int this, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0x44a20fe);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if (iVar2 == 0) {
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar3);
    }
    else if (iVar2 == 1) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(iVar2 + 8);
    }
    else if (iVar2 == 2) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(this + 0x5c) = *(undefined4 *)(iVar2 + 8);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}