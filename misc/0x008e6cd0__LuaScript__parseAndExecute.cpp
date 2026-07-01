// FUNC_NAME: LuaScript::parseAndExecute
void __thiscall LuaScript::parseAndExecute(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0x9222fbbc);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar2);
      break;
    case 1:
      iVar3 = this + 0x58;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 2:
      iVar3 = this + 0x68;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 3:
      iVar3 = this + 0x78;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 4:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x88) = *(undefined4 *)(iVar3 + 8);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}