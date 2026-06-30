// FUNC_NAME: UnknownClass::iterateAndFindElementAtOffset370

void UnknownClass::iterateAndFindElementAtOffset370(int param_1)

{
  undefined4 eaxInitial;
  undefined4 *dataPtr;
  undefined4 **currentNodePtr;
  uint index;
  bool isPercentComplete;
  char iterationMode;
  int bitBase;
  undefined4 *currentElement;
  uint currentIndex;
  uint totalCount;
  undefined4 *elementFromList;
  undefined2 shortBitmapIndex;
  undefined4 elementValue;
  undefined4 **listStart;

  // Initialization with a magic value (0x34f699a5)
  FUN_0043aff0(eaxInitial,0x34f699a5);
  index = currentIndex;
  while( true ) {
    // Determine if we should exit loop based on iteration mode
    if (iterationMode == '\0') {
      isPercentComplete = *listStart == (undefined4 *)0x0;
    }
    else {
      isPercentComplete = index == totalCount;
    }
    if (isPercentComplete) break;
    // Select pointer based on iteration mode
    currentNodePtr = &elementFromList;
    if (iterationMode == '\0') {
      currentNodePtr = listStart;
    }
    // Check type field at offset +6 (short)
    if (*(short *)((int)currentNodePtr + 6) == 0x25e3) {
      // If type matches, treat as handle and extract offset as pointer
      dataPtr = (undefined4 *)(uint)*(ushort *)(currentNodePtr + 1);
    }
    else {
      // Otherwise, get the pointer at offset +4
      dataPtr = currentNodePtr[1];
    }
    // If the extracted pointer is null, store the element's third pointer into this+0x370
    if (dataPtr == (undefined4 *)0x0) {
      currentNodePtr = &elementFromList;
      if (iterationMode == '\0') {
        currentNodePtr = listStart;
      }
      *(undefined4 **)(param_1 + 0x370) = currentNodePtr[2];
    }
    // Advance to next element based on iteration mode
    if (iterationMode == '\0') {
      // Linked list iteration: follow the first pointer (negative offset means back?)
      if ((int)index < 0) {
        listStart = (undefined4 **)((int)listStart + (int)*listStart);
        FUN_0043b140();
        index = currentIndex;
      }
      else if ((int)index < (int)(totalCount - 1)) {
        listStart = (undefined4 **)((int)listStart + (int)*listStart);
        currentIndex = index + 1;
        index = currentIndex;
      }
      else {
        // End of list, set to null sentinel
        listStart = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      // Bitmap-based iteration over an array
      currentIndex = index + 1;
      index = currentIndex;
      if (currentIndex != totalCount) {
        shortBitmapIndex = (short)currentIndex;
        // Check if this index's bit is set in the bitmap
        if ((*(byte *)((currentIndex >> 3) + bitBase) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
          // Bit not set: skip element (null)
          elementFromList = currentElement;
          elementValue = *currentElement;
          currentElement = currentElement + 1;
        }
        else {
          // Bit set: element is valid
          elementFromList = (undefined4 *)0x0;
          elementValue = 0;
        }
      }
    }
  }
  return;
}