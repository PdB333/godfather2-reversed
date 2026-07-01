// FUNC_NAME: LuaScriptManager::processScriptQueue
void __thiscall LuaScriptManager::processScriptQueue(int this, undefined4 scriptId)
{
  char isQueueEmpty;
  int scriptType;
  undefined4 scriptData;
  
  // Initialize script processing
  FUN_0046c710(scriptId);
  FUN_0043aff0(scriptId, 0x257a05b3);
  
  // Loop while there are scripts in the queue
  isQueueEmpty = FUN_0043b120();
  while (isQueueEmpty == '\0') {
    // Get next script from queue
    FUN_0043b210();
    scriptType = FUN_0043ab70();
    
    if (scriptType == 0) {
      // Script type 0: Execute immediate script
      FUN_0043b210();
      scriptData = FUN_0043ab90();
      FUN_004089b0(this + 0x50, scriptData);  // +0x50: script callback handler
    }
    else if (scriptType == 1) {
      // Script type 1: Deferred script execution
      int deferredScript = this + 0x58;  // +0x58: deferred script state
      FUN_0043b210(deferredScript);
      FUN_0043ad10(deferredScript);
    }
    else if (scriptType == 2) {
      // Script type 2: Conditional script
      int conditionData = FUN_0043b210();
      *(bool *)(this + 0x68) = *(int *)(conditionData + 8) == 0;  // +0x68: condition result flag
    }
    
    // Advance to next script in queue
    FUN_0043b1a0();
    isQueueEmpty = FUN_0043b120();
  }
  return;
}