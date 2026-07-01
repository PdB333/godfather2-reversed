// FUNC_NAME: GodfatherGameManager::handleGameStateChange
undefined4 __thiscall GodfatherGameManager::handleGameStateChange(int *this, int gameState)
{
  int currentState;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  currentState = FUN_00466840();  // Get current game state
  if (gameState == currentState) {
    FUN_00937890();  // Handle state re-entry
    (**(code **)(*this + 0x2c))();  // Call virtual function at vtable+0x2c (likely onStateChange)
    return 0;
  }
  currentState = FUN_00466860();  // Get another state value
  if (gameState == currentState) {
    local_c = DAT_01130288;  // Some global data
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);  // Initialize/clear something
    (**(code **)(*this + 0x2c))();  // Call virtual function at vtable+0x2c
    return 0;
  }
  if (gameState == 0) {
    return 1;  // State 0 is valid
  }
  if (gameState == 8) {
    FUN_00937ed0(1);  // Handle state 8 with parameter 1
  }
  else if (gameState == 9) {
    FUN_00937ed0(0xffffffff);  // Handle state 9 with parameter -1
    return 0;
  }
  return 0;
}