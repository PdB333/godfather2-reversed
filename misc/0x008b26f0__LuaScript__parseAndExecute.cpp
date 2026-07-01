// FUNC_NAME: LuaScript::parseAndExecute
void __thiscall LuaScript::parseAndExecute(int *this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0xaeaf6570);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x15,uVar2);  // +0x54: some field
      break;
    case 1:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x17,uVar2);  // +0x5C: some field
      break;
    case 2:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar3 = FUN_004dafd0(uVar2);
      this[0x14] = iVar3;  // +0x50: integer field
      break;
    case 3:
      iVar3 = FUN_0043b210();
      if (*(int *)(iVar3 + 8) == 0) {
        pcVar4 = *(code **)(*this + 0x20);  // vtable offset 0x20
      }
      else {
        pcVar4 = *(code **)(*this + 0x1c);  // vtable offset 0x1C
      }
      (*pcVar4)();
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}