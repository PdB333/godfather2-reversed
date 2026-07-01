// FUNC_NAME: GodfatherGameManager::isDonControlled
bool __thiscall GodfatherGameManager::isDonControlled(int thisPtr, int param_2)
{
  char cVar1;
  
  if (*(char *)(thisPtr + 0x180) != '\0') {
    cVar1 = FUN_007f81c0(thisPtr,*(undefined4 *)(thisPtr + 0x1b4));
    if ((cVar1 != '\0') && ((*(int *)(thisPtr + 400) == 0 || (*(int *)(thisPtr + 400) == param_2))))
    {
      cVar1 = FUN_007f80e0(thisPtr,*(undefined4 *)(thisPtr + 0x1b8));
      if (cVar1 != '\0') {
        return true;
      }
    }
  }
  return false;
}