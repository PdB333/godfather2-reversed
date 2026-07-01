// FUNC_NAME: LuaScriptManager::executeScript
void __thiscall LuaScriptManager::executeScript(int this, undefined4 scriptId)
{
  char isRunning;
  int result;
  undefined4 value;
  
  // Initialize Lua state for this script
  FUN_0046c710(scriptId);
  
  // Push a function reference (likely a hash or callback ID)
  FUN_0043aff0(scriptId, 0x43c8ec5b);
  
  // Check if the Lua script is still running
  isRunning = FUN_0043b120();
  while (isRunning == '\0') {
    // Resume script execution (yield/resume pattern)
    FUN_0043b210();
    
    // Check if there's a return value
    result = FUN_0043ab70();
    if (result == 0) {
      // Resume again to get the value
      FUN_0043b210();
      value = FUN_0043ab90();
      
      // Store the returned value at offset +0x188 (likely a result buffer)
      FUN_00408980(this + 0x188, value);
    }
    
    // Advance to next instruction
    FUN_0043b1a0();
    
    // Re-check if script is still running
    isRunning = FUN_0043b120();
  }
  return;
}