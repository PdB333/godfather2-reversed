// FUNC_NAME: SomeManager::processPendingItems
void __thiscall SomeManager::processPendingItems(int this, undefined4 *outResult)
{
  undefined4 *listHead;
  undefined4 *current;
  undefined4 *temp;
  int *nodeData;
  undefined4 val0, val1, val2, val3;
  int i;
  
  listHead = (undefined4 *)(this + 0x10);
  current = (undefined4 *)*listHead;
  // First loop: just iterates to the end (seems like a bug or dead code)
  for (temp = current; temp != listHead; temp = (undefined4 *)*temp) {
    for (; current != listHead; current = (undefined4 *)*current) {
    }
  }
  
  // Main processing loop
  while (current != listHead) {
    if ((current[2] == 0) || (current[2] == 0x48)) {
      // Remove node from linked list
      current = (undefined4 *)*current;
      nodeData = (int *)current[1];
      *(int *)nodeData[1] = *nodeData;
      *(int *)(*nodeData + 4) = nodeData[1];
      if (nodeData[2] != 0) {
        FUN_004daf90(nodeData + 2); // Some cleanup function
      }
      FUN_009c8f10(nodeData); // Free memory
    }
    else {
      FUN_0089e6d0(current + 2); // Process pending item
      current = (undefined4 *)*current;
    }
  }
  
  // Call some update functions 4 times
  i = 4;
  do {
    FUN_0089cc10(); // Update function
    i = i + -1;
  } while (i != 0);
  
  // Get result from some manager
  i = FUN_0089c8d0(); // Get some manager instance
  if (i != 0) {
    val0 = *(undefined4 *)(i + 0x60);
    val1 = *(undefined4 *)(i + 100); // 0x64
    val2 = *(undefined4 *)(i + 0x68);
    val3 = *(undefined4 *)(i + 0x6c);
    *outResult = val0;
    outResult[1] = val1;
    outResult[2] = val2;
    outResult[3] = val3;
  }
  return;
}