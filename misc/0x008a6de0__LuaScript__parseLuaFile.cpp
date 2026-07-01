// FUNC_NAME: LuaScript::parseLuaFile
void __thiscall LuaScript::parseLuaFile(int thisPtr, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_008a13c0(param_2);
  FUN_0043aff0(param_2,0xc17ed7a5);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if (iVar2 == 0) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x58) = *(undefined4 *)(iVar2 + 8);
    }
    else if (iVar2 == 1) {
      iVar2 = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x5c) = *(undefined4 *)(iVar2 + 8);
    }
    else if (iVar2 == 2) {
      FUN_0043b210();
      iVar2 = FUN_0043ab90();
      if (iVar2 == 0) {
        *(undefined4 *)(thisPtr + 0x60) = 0;
      }
      else {
        uVar3 = FUN_005e3300(iVar2);
        *(undefined4 *)(thisPtr + 0x60) = uVar3;
      }
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}