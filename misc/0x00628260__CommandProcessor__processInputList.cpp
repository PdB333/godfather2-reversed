// FUNC_NAME: CommandProcessor::processInputList
void CommandProcessor::processInputList(int param_1, int* inputList)
{
  int* currentEntry;
  int* in_EAX; // actually inputList, but reuse original name for clarity
  undefined4* stackPtr;
  int* stackPosition;
  undefined4 value;
  int* esi_backup; // unaff_ESI

  if (param_1 != 0) {
    // Begin frame or push operation
    FUN_00625ca0();
    stackPtr = (undefined4 *)FUN_00633cb0(); // Get current timestamp or sequence
    int bufferPos = *(int *)(this + 8); // Current stack pointer
    *(undefined4 *)(bufferPos - 8) = *stackPtr;
    *(undefined4 *)(bufferPos - 4) = stackPtr[1];
    stackPosition = (int *)(bufferPos - 8);
    if ((stackPosition != (int *)0x0) && (*stackPosition == 0)) {
      // Stack entry is empty, reclaim space
      *(int **)(this + 8) = stackPosition;
      if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        // Buffer full, flush/expand
        FUN_00627360();
      }
      stackPtr = *(undefined4 **)(this + 8);
      *stackPtr = 5; // Command id 5
      value = FUN_00637c50(0,0); // Generate unique id or timestamp
      stackPtr[1] = value;
      *(int *)(this + 8) += 8;
      FUN_00625ca0();
      stackPtr = *(undefined4 **)(this + 8);
      // Copy previous two entries (the ones we just moved)
      *stackPtr = stackPtr[-4];
      stackPtr[1] = stackPtr[-3];
      *(int *)(this + 8) += 8;
      // Compact: shift stack back by 16 bytes (two entries)
      FUN_00633d60(this + 0x40, *(int *)(this + 8) - 0x10, *(int *)(this + 8) - 8);
      *(int *)(this + 8) -= 0x10;
    }
    FUN_00625670(); // Commit/pop frame
  }
  // Process input list: each entry is a pair of ints (command + data)
  in_EAX = inputList;
  while (*in_EAX != 0) {
    FUN_00625ca0();
    FUN_00625d70();
    int stackPos = *(int *)(this + 8);
    // Move and compact: copy two entries from stackPos-0x10..stackPos-8 to stackPos-0x18..stackPos-0x10
    FUN_00633d60(stackPos - 0x18, stackPos - 0x10, stackPos - 8);
    *(int *)(this + 8) -= 0x10; // Pop two entries
    in_EAX += 2; // Advance to next input pair
  }
  *(undefined4 *)(this + 8) = *(undefined4 *)(this + 8); // Redundant assignment
  return;
}