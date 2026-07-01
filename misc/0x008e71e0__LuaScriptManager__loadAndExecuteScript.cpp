// FUNC_NAME: LuaScriptManager::loadAndExecuteScript
void __thiscall LuaScriptManager::loadAndExecuteScript(int this, undefined4 scriptName)
{
  char cVar1;
  int iVar2;
  
  FUN_0046c710(scriptName);  // Load script file
  FUN_0043aff0(scriptName,0x1f1d5de4);  // Register script with hash
  cVar1 = FUN_0043b120();  // Check if script execution is complete
  while (cVar1 == '\0') {
    FUN_0043b210();  // Execute next script instruction
    iVar2 = FUN_0043ab70();  // Get script return type
    if (iVar2 == 0) {
      iVar2 = FUN_0043b210();  // Get return value
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(iVar2 + 8);  // Store integer return value at +0x50
    }
    else if (iVar2 == 1) {
      iVar2 = FUN_0043b210();  // Get return value
      *(undefined4 *)(this + 0x54) = *(undefined4 *)(iVar2 + 8);  // Store string/object return value at +0x54
    }
    FUN_0043b1a0();  // Advance script execution
    cVar1 = FUN_0043b120();  // Check completion again
  }
  return;
}