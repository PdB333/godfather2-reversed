// FUNC_NAME: LuaScript::parseScriptBlock
void __thiscall LuaScript::parseScriptBlock(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0xf40bce26);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x58,uVar2);
      break;
    case 1:
      iVar3 = FUN_0043b210();
      *(int *)(this + 0x50) = *(int *)(iVar3 + 8) * 10000;
      break;
    case 2:
      iVar3 = FUN_0043b210();
      *(int *)(this + 0x54) = *(int *)(iVar3 + 8) * 10000;
      break;
    case 3:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x60;
      goto LAB_008261fa;
    case 4:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = this + 0x68;
LAB_008261fa:
      FUN_00408980(iVar3,uVar2);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}