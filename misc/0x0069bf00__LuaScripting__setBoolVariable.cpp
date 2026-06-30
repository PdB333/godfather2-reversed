// FUNC_NAME: LuaScripting::setBoolVariable
void LuaScripting::setBoolVariable(int scriptContext, bool value)
{
  int iVar1;
  char *pcVar2;
  int local_10 [3];
  code *local_4;
  
  FUN_004d3bc0(scriptContext); // lua_gettop or similar stack manipulation
  iVar1 = FUN_00699ff0(); // check if variable exists or is valid
  if ((iVar1 != 0) || ((-1 < DAT_00e506ac && (DAT_00e506ac < DAT_01129f90 - DAT_01129f8c >> 2)))) {
    FUN_004d3bc0(scriptContext); // push value onto Lua stack
    pcVar2 = "true";
    if (value == '\0') {
      pcVar2 = "false";
    }
    FUN_0069b380(local_10); // create Lua string object
    FUN_004d3d90(pcVar2); // push string onto Lua stack
    if (local_10[0] != 0) {
      (*local_4)(local_10[0]); // call Lua function or set global
    }
  }
  return;
}