// FUNC_NAME: StreamManager::updateStreamPosition
void __thiscall StreamManager::updateStreamPosition(int thisPtr, int param_2)
{
  int iVar1;
  
  iVar1 = param_2 - *(int *)(thisPtr + 200); // +0xC8: stream position offset
  if (iVar1 != 0) {
    *(int *)(thisPtr + 200) = param_2; // +0xC8: stream position
    FUN_008c7800(*(undefined4 *)(thisPtr + 0x40), thisPtr, iVar1); // +0x40: stream handle
  }
  return;
}