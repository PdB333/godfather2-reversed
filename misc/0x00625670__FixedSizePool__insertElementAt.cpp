// FUNC_NAME: FixedSizePool::insertElementAt
void __fastcall FixedSizePool::insertElementAt(void *thisPtr, int param_2)
{
  int in_EAX; // actually thisPtr base
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (param_2 < 1) {
    // Insert at front of pool (index 0)
    puVar1 = (undefined4 *)FUN_00625430(); // likely getPoolStart or getFirstFreeSlot
  }
  else {
    // Calculate pointer to element at given index in pool
    // Pool data starts at thisPtr + 0xC with element size 8 bytes
    puVar1 = (undefined4 *)(*(int *)(in_EAX + 0xc) + -8 + param_2 * 8);
  }
  
  // Shift elements to make room at puVar1
  // Pool has a cursor/end pointer at thisPtr + 8
  for (puVar2 = *(undefined4 **)(in_EAX + 8); puVar1 < puVar2; puVar2 = puVar2 + -2) {
    *puVar2 = puVar2[-2];
    puVar2[1] = puVar2[-1];
  }
  
  // Copy the current first element into the created gap
  puVar2 = *(undefined4 **)(in_EAX + 8);
  *puVar1 = *puVar2;
  puVar1[1] = puVar2[1];
  
  return;
}