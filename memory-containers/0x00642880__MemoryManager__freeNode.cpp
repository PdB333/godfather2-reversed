// FUNC_NAME: MemoryManager::freeNode
void __fastcall MemoryManager::freeNode(int unused, int *param_2, int *param_3)
{
  int nodeIndex;
  int currentIndex;
  uint linkValue;
  
  if (in_EAX != -1) {
    currentIndex = *param_2;
    if (currentIndex == -1) {
      // Empty list, just set it
      *param_2 = in_EAX;
      return;
    }
    do {
      // +0x0C: pointer to link data array, shift 6 bits, mask 0x3FFFF
      linkValue = *(int *)(*(int *)(*param_3 + 0xc) + currentIndex * 4) >> 6 & 0x3ffff;
      if (linkValue == 0x1fffe) break;
      currentIndex = (linkValue - 0x1fffe) + currentIndex;
    } while (currentIndex != -1);
    FUN_00642550(); // Likely assert or error handler
  }
  return;
}