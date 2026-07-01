// FUNC_NAME: LuaScriptManager::executeScriptWithArgs
void __thiscall executeScriptWithArgs(int this, int *scriptContext)
{
  char cVar1;
  int iVar2;
  int scriptState;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_14 = 0;
  local_18 = 0;
  local_10 = 0;
  local_c = 0;
  
  // Call virtual function at vtable+0x1cc (likely lua_gettop or similar)
  cVar1 = (**(code **)(*scriptContext + 0x1cc))(&local_18);
  
  // Loop while there are more arguments and we haven't hit a stop condition
  while ((cVar1 != '\0' &&
         (((scriptState != 6 && scriptState != 7) ||
          (iVar2 = (**(code **)(*scriptContext + 500))(&scriptState), iVar2 != 0))))) {
    // Call virtual function at vtable+0x1d0 (likely lua_next or similar)
    cVar1 = (**(code **)(*scriptContext + 0x1d0))(&scriptState, &scriptState);
  }
  
  // Call virtual function at vtable+0x1f0 (likely lua_pcall or similar)
  (**(code **)(*scriptContext + 0x1f0))(&scriptState, &local_14);
  
  // Call virtual function at vtable+0xa4 (likely lua_settop or cleanup)
  (**(code **)(*scriptContext + 0xa4))(this, &local_18);
  
  return;
}