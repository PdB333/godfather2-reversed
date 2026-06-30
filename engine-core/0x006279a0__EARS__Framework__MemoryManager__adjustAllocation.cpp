// FUNC_NAME: EARS::Framework::MemoryManager::adjustAllocation
int EARS::Framework::MemoryManager::adjustAllocation(int param_1, uint param_2)
{
  int *piVar1;
  int in_EAX;
  int iVar2;
  int unaff_ESI;
  
  if (param_2 == 0) {
    if (in_EAX == 0) {
      return 0;
    }
    (*DAT_012059e0)(); // likely a memory free function
    in_EAX = 0;
  }
  else if (param_2 < 0xfffffffd) {
    in_EAX = (*DAT_012059dc)(); // likely a memory allocation function
    if (in_EAX == 0) {
      if (unaff_ESI == 0) {
        return 0;
      }
      iVar2 = FUN_00635a80(); // likely a memory reallocation or error handler
      return iVar2;
    }
  }
  else {
    FUN_00633920(); // likely a memory cleanup or error handler
  }
  if (unaff_ESI != 0) {
    piVar1 = (int *)(*(int *)(unaff_ESI + 0x10) + 0x24); // +0x10: pointer to memory block header, +0x24: size field
    *piVar1 = *piVar1 - param_1;
    piVar1 = (int *)(*(int *)(unaff_ESI + 0x10) + 0x24);
    *piVar1 = *piVar1 + param_2;
  }
  return in_EAX;
}