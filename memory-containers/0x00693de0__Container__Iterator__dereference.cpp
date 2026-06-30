// FUNC_NAME: Container::Iterator::dereference
// Address: 0x00693de0
// Purpose: Dereference an iterator with debug bounds checking.
//   The iterator structure is assumed to hold:
//     +0x00: pointer to container (used to access sentinel node)
//     +0x04: pointer to current node
//   The container holds (at +0x04) a sentinel pointer (typically head node for circular list).
//   Node layout: next (4), prev (4), data (4) => data at offset +0x0C.
//   If the current node equals the sentinel, it indicates end-of-list; the function asserts.
//   Returns a pointer to the data portion of the current node.

int __fastcall DereferenceIterator(int *iteratorPtr)
{
  // interpreter: "this" in ECX, but decompiled as int* param_1
  int *containerPtr = (int *)iteratorPtr[0];  // container pointer
  int currentNode = iteratorPtr[1];           // current node pointer

  if (containerPtr == 0) {
    AssertionFailed();  // FUN_00b97aea - debug break / assert
  }
  // Compare current node to the sentinel stored at container+0x04
  if (currentNode == *(int *)((int)containerPtr + 4)) {
    AssertionFailed();  // out-of-bounds (end iterator)
  }
  // Return pointer to data at offset 0x0C within the node
  return currentNode + 12;
}