// FUNC_NAME: LuaScript::executeScriptBlock
void __thiscall LuaScript::executeScriptBlock(int this, undefined4 scriptData)
{
  char isRunning;
  int scriptResult;
  undefined4 scriptValue;
  
  // Initialize the Lua state with the script data
  luaL_loadBuffer(scriptData);
  lua_pcall(scriptData,0,0,0x421600bd);
  
  // Main execution loop - keep processing until script finishes
  isRunning = lua_isRunning();
  while (isRunning == '\0') {
    // Resume the Lua coroutine
    lua_resume();
    scriptResult = lua_getResult();
    if (scriptResult == 0) {
      // Script yielded with a value - store it
      lua_resume();
      scriptValue = lua_getValue();
      // Store the yielded value at this+0x50 (likely a script return value slot)
      *(undefined4 *)(this + 0x50) = scriptValue;
    }
    else if (scriptResult == 1) {
      // Script yielded with a thread reference
      scriptResult = lua_resume();
      // Store the thread reference at this+0x58 (likely a coroutine handle)
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(scriptResult + 8);
    }
    // Advance the script execution
    lua_advance();
    isRunning = lua_isRunning();
  }
  return;
}