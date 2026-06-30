// FUNC_NAME: parseDataBlockIntoList
void __thiscall parseDataBlockIntoList(int thisPtr, undefined4 inputData)
{
  int *listPtr;
  undefined4 *entryDataPtr;
  undefined4 tempValue;
  undefined4 **iterator;
  uint currentIndex;
  undefined4 **nodePtr;
  bool loopCondition;
  char isIndexed;
  int bitFieldBase;
  undefined4 *indexedArray;
  uint totalCount;
  uint indexCounter;
  undefined4 *currentEntry;
  undefined2 indexShort;
  undefined4 entryData;
  undefined4 **linkedListRoot;

  // Initialize parser/hash with input data and a constant (possibly a string ID or key)
  FUN_0043aff0(inputData, 0x373688);
  nodePtr = linkedListRoot;
  currentIndex = indexCounter;
  while (true) {
    if (isIndexed == '\0') {
      loopCondition = *nodePtr == (undefined4 *)0x0;
    }
    else {
      loopCondition = currentIndex == totalCount;
    }
    if (loopCondition) break;
    iterator = &currentEntry;
    if (isIndexed == '\0') {
      iterator = nodePtr;
    }
    // Check if current node type identifier equals 0x25e3 (likely a sentinel or type tag)
    if (*(short *)((int)iterator + 6) == 0x25e3) {
      entryDataPtr = (undefined4 *)(uint)*(ushort *)(iterator + 1);
    }
    else {
      entryDataPtr = iterator[1];
    }
    if (entryDataPtr == (undefined4 *)0x0) {
      // Null entry: reset the list at thisPtr+0x50 and try to parse next node
      iterator = &currentEntry;
      if (isIndexed == '\0') {
        iterator = nodePtr;
      }
      if (*(short *)((int)iterator + 6) == 0x25e3) {
        if (*nodePtr == (undefined4 *)0x0) {
          iterator = (undefined4 **)&DAT_00e2a89b; // likely a default/empty string
        }
        else {
          iterator = (undefined4 **)((int)nodePtr[2] + (int)*nodePtr);
        }
      }
      else {
        iterator = iterator + 2;
      }
      listPtr = (int *)(thisPtr + 0x50);
      FUN_004086d0(listPtr);      // Clear/empty the list
      FUN_00408310(listPtr);      // Possibly release/destruct
      nodePtr = linkedListRoot;
      currentIndex = indexCounter;
      if ((iterator != (undefined4 **)0x0) && (*(char *)iterator != '\0')) {
        tempValue = FUN_004dafd0(iterator);  // Convert something to a value
        FUN_00408260(listPtr, tempValue);    // Append value to list
        nodePtr = linkedListRoot;
        if (*listPtr != 0) {
          FUN_00407e60(thisPtr + 0x3c, listPtr);  // Sort or process the list
          nodePtr = linkedListRoot;
        }
      }
    }
    else if ((entryDataPtr == (undefined4 *)0x1) && (*(int *)(thisPtr + 0x58) == (int)entryDataPtr - 1U)) {
      // Special case: entry is 1 and thisPtr+0x58 is 0 -> set thisPtr+0x58 to a new pointer
      iterator = &currentEntry;
      if (isIndexed == '\0') {
        iterator = nodePtr;
      }
      if (*(short *)((int)iterator + 6) == 0x25e3) {
        if (*nodePtr == (undefined4 *)0x0) {
          *(undefined1 **)(thisPtr + 0x58) = &DAT_00e2a89b;
        }
        else {
          *(int *)(thisPtr + 0x58) = (int)nodePtr[2] + (int)*nodePtr;
        }
      }
      else {
        *(undefined4 ***)(thisPtr + 0x58) = iterator + 2;
      }
    }
    // Advance to next node based on iteration mode
    if (isIndexed == '\0') {
      // Linked list mode: move to next node using stored size (offset 0)
      if ((int)currentIndex < 0) {
        linkedListRoot = (undefined4 **)((int)nodePtr + (int)*nodePtr);
        FUN_0043b140();  // Possibly advance iterator internal state
        nodePtr = linkedListRoot;
        currentIndex = indexCounter;
      }
      else if ((int)currentIndex < (int)(totalCount - 1)) {
        indexCounter = currentIndex + 1;
        linkedListRoot = (undefined4 **)((int)nodePtr + (int)*nodePtr);
        nodePtr = (undefined4 **)((int)nodePtr + (int)*nodePtr);
        currentIndex = indexCounter;
      }
      else {
        linkedListRoot = (undefined4 **)&DAT_01163cf8;
        nodePtr = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      // Indexed mode: advance through array, skipping entries with bitfield mask
      indexCounter = currentIndex + 1;
      currentIndex = indexCounter;
      if (indexCounter != totalCount) {
        indexShort = (short)indexCounter;
        if ((*(byte *)((indexCounter >> 3) + bitFieldBase) & (byte)(1 << ((byte)indexCounter & 7))) == 0) {
          entryData = *indexedArray;
          currentEntry = indexedArray;
          indexedArray = indexedArray + 1;
        }
        else {
          currentEntry = (undefined4 *)0x0;
          entryData = 0;
        }
      }
    }
  }
  return;
}