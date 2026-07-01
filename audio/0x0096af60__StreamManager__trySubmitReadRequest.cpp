// FUNC_NAME: StreamManager::trySubmitReadRequest
undefined1 StreamManager::trySubmitReadRequest(undefined4 param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
  if ((DAT_011308b4 != '\0') && (*(int *)(DAT_01129930 + 0xbc) < *(int *)(DAT_01129930 + 0xb4))) {
    *(int *)(DAT_01129930 + 0xbc) = *(int *)(DAT_01129930 + 0xbc) + 1;
    FUN_00968cc0(param_1);
    uVar1 = 1;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_011308c0);
  return uVar1;
}