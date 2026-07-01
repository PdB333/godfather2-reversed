// FUNC_NAME: LuaScript::executeScript
void __thiscall LuaScript::executeScript(int *this, undefined4 scriptData)
{
  char isDone;
  undefined4 commandType;
  int intValue;
  code *vtableFunc;
  
  // Initialize script execution with a hash/ID
  FUN_0043aff0(scriptData, 0x82610853);
  
  isDone = FUN_0043b120();
  while (isDone == '\0') {
    // Read next command from script stream
    FUN_0043b210();
    commandType = FUN_0043ab70();
    
    switch(commandType) {
    case 0:
      // Command type 0: Set float value at offset +0x15
      FUN_0043b210();
      commandType = FUN_0043ab90();
      FUN_004089b0(this + 0x15, commandType);
      break;
    case 1:
      // Command type 1: Set float value at offset +0x17
      FUN_0043b210();
      commandType = FUN_0043ab90();
      FUN_004089b0(this + 0x17, commandType);
      break;
    case 2:
      // Command type 2: Set integer value at offset +0x14
      FUN_0043b210();
      commandType = FUN_0043ab90();
      intValue = FUN_004dafd0(commandType);
      this[0x14] = intValue;
      break;
    case 3:
      // Command type 3: Call a virtual function based on a condition
      intValue = FUN_0043b210();
      if (*(int *)(intValue + 8) == 0) {
        pcVar4 = *(code **)(*this + 0x20);
      }
      else {
        pcVar4 = *(code **)(*this + 0x1c);
      }
      (*pcVar4)();
    }
    FUN_0043b1a0();
    isDone = FUN_0043b120();
  }
  return;
}