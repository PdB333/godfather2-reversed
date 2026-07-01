// FUNC_NAME: InputManager::toggleCursorVisibility
void __fastcall InputManager::toggleCursorVisibility(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_006b4860(); // likely getCurrentPlatform() or isConsole()
  if (iVar1 == 0) { // PC platform
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_0043b870(DAT_0112af98); // getInputManager() or getActiveController()
    }
    if ((~*(byte *)(iVar1 + 0x50) & 1) == 0) { // check cursor visibility flag at +0x50
      FUN_007894e0(); // showCursor()
    }
  }
  else { // console platform
    if (param_1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_0043b870(DAT_0112af98); // getInputManager() or getActiveController()
    }
    if ((~*(byte *)(iVar1 + 0x50) & 1) != 0) { // check cursor visibility flag at +0x50
      FUN_007894b0(); // hideCursor()
      return;
    }
  }
  return;
}