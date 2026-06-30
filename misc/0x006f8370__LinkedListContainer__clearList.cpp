// FUNC_NAME: LinkedListContainer::clearList
void __fastcall LinkedListContainer::clearList(int *thisPtr)
{
  int *nodePtr;
  int *nextPtr;

  nodePtr = (int *)*thisPtr;
  while (nodePtr) {
    nextPtr = (int *)nodePtr[5]; // nodePtr + 0x14, next pointer
    if (nodePtr[3]) { // nodePtr + 0xC
      FUN_004daf90(nodePtr + 3);
    }
    if (nodePtr[1]) { // nodePtr + 0x4
      FUN_004daf90(nodePtr + 1);
    }
    // call allocator's virtual deallocate function (vtable+4) with node and 0
    (*(void (__thiscall **)(int *, int))(*((int *)thisPtr[4] + 1)))(nodePtr, 0);
    nodePtr = nextPtr;
    *thisPtr = (int)nextPtr;
  }
  thisPtr[1] = 0; // clear temporary next pointer
  *thisPtr = 0;   // clear head
  thisPtr[2] = 0; // clear count
}