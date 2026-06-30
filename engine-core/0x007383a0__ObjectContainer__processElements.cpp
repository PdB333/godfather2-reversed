// FUNC_NAME: ObjectContainer::processElements
void __fastcall ObjectContainer::processElements(int thisPtr)
{
  // thisPtr: pointer to the container or manager object
  // +0x1C: handle or pointer to the collection being iterated
  int collectionHandle = *(int *)(thisPtr + 0x1C);

  // Check if the collection is not in a certain state (e.g., not currently active)
  if (!FUN_00738320(collectionHandle)) // likely IsActive or IsValid
  {
    // Initialize a stack-allocated iterator (size: 0x48 + 0x48 = 0x90 bytes)
    int iteratorState[18]; // 0x48 bytes, holds iterator data
    char iteratorBuffer[72]; // 0x48 bytes, additional iterator data? The decompiler shows two arrays.

    // Initialize the iterator to start from the beginning (flag = 0)
    FUN_00405e40(iteratorState, collectionHandle, 0); // InitIterator

    // Get the first element's handle
    int currentHandle = FUN_00405f20(iteratorBuffer); // GetNext / Advance

    // Check if the iterator has more elements
    while (FUN_00405f90(currentHandle) != 0) // IteratorDone? Returns non-zero if valid
    {
      // Retrieve the current item from the iterator
      int currentItem = FUN_00405f40(); // GetCurrentItem

      // Check if the item is now active
      if (FUN_00738320(currentItem) != 0) // IsActive / IsValid
      {
        return; // Early exit: stop processing if any item becomes active
      }

      // Call a virtual function on the item (vtable entry at offset +4)
      // The iterator's first field (iteratorState[0]) is a vtable pointer to the collection?
      (**(void (__thiscall**)(int))*((int *)&iteratorState[0] + 4))(); // call vfunc+4

      // Advance to the next element
      currentHandle = FUN_00405f20(iteratorBuffer); // GetNext
    }
  }
}