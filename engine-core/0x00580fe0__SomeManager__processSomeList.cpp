// FUNC_NAME: SomeManager::processSomeList
void SomeManager::processSomeList(int param_1, int param_2)
{
  int iVar1;
  
  FUN_00581080(); // Likely a setup or validation function
  iVar1 = 0;
  if (0 < *(int *)(param_2 + 0x1c)) { // +0x1c: count of items in list
    do {
      FUN_00581220(param_1); // Process each item at param_1 (0x20 stride per item)
      iVar1 = iVar1 + 1;
      param_1 = param_1 + 0x20; // Advance to next item (each item is 0x20 bytes)
    } while (iVar1 < *(int *)(param_2 + 0x1c));
  }
  return;
}