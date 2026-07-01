// FUNC_NAME: DebugKeyboardHandler::handleDebugInput
undefined4 __thiscall DebugKeyboardHandler::handleDebugInput(int this, int inputAction)
{
  int actionCode;
  
  // Check if debug mode is enabled at offset +0x50
  if (*(int *)(this + 0x50) == 0) {
    // Handle specific debug action IDs
    if (inputAction == 8) {
      // Toggle debug overlay
      FUN_009236d0();
      return 0;
    }
    if (inputAction == 9) {
      // Toggle debug camera
      FUN_00923710();
      return 0;
    }
    if (inputAction == 6) {
      // Toggle collision debug
      FUN_00923750();
      return 0;
    }
    if (inputAction == 7) {
      // Toggle AI debug
      FUN_00923770();
      return 0;
    }
    
    // Dynamic action: first get action codes from input system
    actionCode = FUN_00466840(); // Get action code for first configurable action
    if (inputAction == actionCode) {
      // Show entity debug info
      FUN_00924ea0();
      return 0;
    }
    
    actionCode = FUN_00466860(); // Get action code for second configurable action
    if (inputAction == actionCode) {
      // Toggle console display
      FUN_00924b10();
    }
  }
  return 0;
}