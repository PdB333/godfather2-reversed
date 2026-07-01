// FUNC_NAME: StreamManager::setActive
void __thiscall StreamManager::setActive(int this, char isActive)
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  // +0x04: active flag
  if (*(char *)(this + 4) == '\0') {
    *(char *)(this + 4) = isActive;
    return;
  }
  
  // When deactivating, release all 8 stream slots
  if (isActive == '\0') {
    // +0x104: array of 8 stream slot pointers (each 4 bytes)
    piVar3 = (int *)(this + 0x104);
    iVar2 = 8;
    do {
      iVar1 = *piVar3;
      if (iVar1 != 0) {
        // Release stream handle
        FUN_005e6820(iVar1, 0, 0);
        // Free stream slot
        FUN_005e6660(iVar1);
        *piVar3 = 0;
      }
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  
  *(char *)(this + 4) = isActive;
  return;
}