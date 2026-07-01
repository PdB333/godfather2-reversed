// FUNC_NAME: InputManager::checkControllerConnected
void __fastcall InputManager::checkControllerConnected(int param_1)
{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0043b870(DAT_0112af98); // InputManager::getControllerState - returns pointer to controller state array
  }
  if ((~*(byte *)(iVar1 + 0x50) & 1) != 0) { // Check if controller is connected (bit 0 of flags at +0x50)
    FUN_007894b0(); // InputManager::onControllerDisconnected
    return;
  }
  return;
}