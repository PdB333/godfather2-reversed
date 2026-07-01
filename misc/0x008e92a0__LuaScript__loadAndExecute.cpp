// FUNC_NAME: LuaScript::loadAndExecute
void __thiscall LuaScript::loadAndExecute(int this, undefined4 scriptName)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0046c710(scriptName); // likely luaL_loadfile or similar
  FUN_0043aff0(scriptName,0x596c7dd5); // likely lua_pcall with a hash/checksum
  cVar1 = FUN_0043b120(); // check if lua state is still valid
  while (cVar1 == '\0') {
    FUN_0043b210(); // lua_gettop or similar
    iVar2 = FUN_0043ab70(); // get next instruction type
    if (iVar2 == 0) {
      iVar2 = this + 0x50; // +0x50: some member pointer
      FUN_0043b210(iVar2); // push onto stack
      FUN_0043ad10(iVar2); // execute function
    }
    else if (iVar2 == 1) {
      FUN_0043b210(); // push something
      uVar3 = FUN_0043ab90(); // get string value
      FUN_004089b0(this + 0x60,uVar3); // +0x60: store string member
    }
    else if (iVar2 == 2) {
      FUN_0043b210(); // push something
      uVar3 = FUN_0043ab90(); // get string value
      FUN_004089b0(this + 0x68,uVar3); // +0x68: store another string member
    }
    FUN_0043b1a0(); // pop stack
    cVar1 = FUN_0043b120(); // check state again
  }
  return;
}