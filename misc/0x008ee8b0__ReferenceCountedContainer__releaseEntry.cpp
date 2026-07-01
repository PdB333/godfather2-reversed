// FUNC_NAME: ReferenceCountedContainer::releaseEntry

int __thiscall ReferenceCountedContainer::releaseEntry(int this, int *pEntry)
{
  int *pNode; // local_8 - pointer to container node
  int *pElement; // local_4 - pointer to element inside node
  int result; // iVar1

  if (pEntry != 0) {
    // Retrieve the node containing pEntry and the base element pointer
    findNodeAndElement(&pNode, &pEntry);

    // Assert: the node must be non-null and must equal the sentinel node at this+0x38
    // (if node is null or not the sentinel, something is wrong)
    if ((pNode == 0) || (pNode != *(int **)(this + 0x38))) {
      assert(); // FUN_00b97aea
    }

    result = *(int *)(this + 0x3c); // probably a current/active element pointer or count

    if (pElement != result) {
      // Validate pNode again (should be same as before)
      if (pNode == 0) {
        assert();
      }
      // Ensure pElement is not the first element of the node (pNode+4)
      if (pElement == *(int **)(pNode + 4)) {
        assert();
      }

      // Decrement reference count at offset 0x10 of the element
      *(int *)(pElement + 0x10) = *(int *)(pElement + 0x10) - 1;

      // Re-check if pElement is first element (likely for debug)
      if (pElement == *(int **)(pNode + 4)) {
        assert();
      }

      result = *(int *)(pElement + 0x10);
      // If reference count reached zero, remove the entry from the container
      if (result == 0) {
        removeNode(&pNode, pNode, pElement); // FUN_008ee030
      }
      return result;
    }
  }
  return -1;
}