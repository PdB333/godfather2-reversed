// FUNC_NAME: LuaScript::parseTableFields
void __thiscall LuaScript::parseTableFields(int this, undefined4 luaState)
{
  char cVar1;
  int iVar2;
  
  // Push the table onto the stack and set the table index
  lua_pushvalue(luaState, -1);
  lua_settop(luaState, 0x842eb5b);
  
  // Start iterating over table fields
  cVar1 = lua_next(luaState, -2);
  while (cVar1 == '\0') {
    // Get the key (field name)
    lua_pushvalue(luaState, -2);
    iVar2 = lua_type(luaState, -1);
    
    if (iVar2 == 0) {
      // String key - read string value
      iVar2 = lua_tostring(luaState, -1);
      *(undefined4 *)(this + 0x54) = *(undefined4 *)(iVar2 + 8); // +0x54: stringField1
    }
    else if (iVar2 == 1) {
      // Number key - read number value
      iVar2 = lua_tonumber(luaState, -1);
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(iVar2 + 8); // +0x58: numberField
    }
    else if (iVar2 == 2) {
      // Boolean key - read boolean value
      iVar2 = lua_toboolean(luaState, -1);
      *(bool *)(this + 0x50) = *(int *)(iVar2 + 8) != 0; // +0x50: boolField
    }
    
    // Pop the value, keep key for next iteration
    lua_pop(luaState, 1);
    cVar1 = lua_next(luaState, -2);
  }
  return;
}