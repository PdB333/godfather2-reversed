// FUNC_NAME: LuaScript::loadAndExecuteScript
void __thiscall LuaScript::loadAndExecuteScript(int this, undefined4 scriptData)
{
  char hasError;
  undefined4 tokenType;
  int tokenValue;
  
  // Initialize Lua state and load script
  FUN_0046c710(scriptData);
  FUN_0043aff0(scriptData, 0xf776aa00);
  
  // Check for initial error
  hasError = FUN_0043b120();
  do {
    if (hasError != '\0') {
      return;
    }
    
    // Get next token from script parser
    FUN_0043b210();
    tokenType = FUN_0043ab70();
    
    switch(tokenType) {
    case 0: // Integer assignment
      tokenValue = FUN_0043b210();
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(tokenValue + 8); // +0x50: scriptIntValue
      break;
    case 1: // Float assignment
      tokenValue = FUN_0043b210();
      *(undefined4 *)(this + 0x54) = *(undefined4 *)(tokenValue + 8); // +0x54: scriptFloatValue
      break;
    case 2: // Boolean assignment
      tokenValue = FUN_0043b210();
      *(undefined1 *)(this + 0x58) = *(undefined1 *)(tokenValue + 8); // +0x58: scriptBoolValue
      break;
    case 3: // String assignment
      FUN_0043b210();
      tokenType = FUN_0043ab90();
      FUN_004089b0(this + 0x5c, tokenType); // +0x5c: scriptStringValue (String object)
      break;
    case 4: // Array assignment
      FUN_0043b210();
      tokenType = FUN_0043ab90();
      tokenValue = this + 100;
      goto LAB_0089606f;
    case 5: // Table assignment
      FUN_0043b210();
      tokenType = FUN_0043ab90();
      tokenValue = this + 0x6c;
LAB_0089606f:
      FUN_00408980(tokenValue, tokenType); // Assign array/table value
    }
    
    // Advance to next token
    FUN_0043b1a0();
    hasError = FUN_0043b120();
  } while( true );
}