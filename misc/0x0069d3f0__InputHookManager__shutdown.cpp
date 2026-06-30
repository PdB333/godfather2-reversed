// FUNC_NAME: InputHookManager::shutdown
void InputHookManager::shutdown(char param_1)

{
  if (DAT_01129fac != '\0') {
    if (param_1 == '\0') {
      FUN_0069d340();  // likely uninstallKeyboardHook
      FUN_0069d0c0();  // likely uninstallMouseHook
      return;
    }
    FUN_0069d060();  // likely uninstallAllHooks
    if (DAT_01129fb0 != (HHOOK)0x0) {
      UnhookWindowsHookEx(DAT_01129fb0);  // +0x4? global hook handle
      DAT_01129fb0 = (HHOOK)0x0;
    }
  }
  return;
}