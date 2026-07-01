// FUNC_NAME: LuaManager::processCommandFromString
void __thiscall LuaManager::processCommandFromString(int thisPtr, undefined4 *commandParts)
{
  char cVar1;
  int assetHandle;
  int unaff_ESI;
  
  assetHandle = FUN_004544a0(*commandParts,commandParts[1]); // Look up asset by identifier
  if (assetHandle != 0) {
    commandParts = (undefined4 *)0x0;
    // +0x10: virtual method index for Lua processing
    cVar1 = (**(code **)(*(int *)(assetHandle + -0x58) + 0x10))(0x4ecfbe13,&commandParts);
    if ((cVar1 != '\0') && (unaff_ESI != 0)) {
      // +600: method offset for finalizing Lua command execution
      (**(code **)(*(int *)(thisPtr + -0x58) + 600))(unaff_ESI);
    }
  }
  return;
}