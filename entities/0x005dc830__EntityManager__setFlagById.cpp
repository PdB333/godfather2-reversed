// FUNC_NAME: EntityManager::setFlagById

// 0x005dc830 - Sets a byte flag on all entities with a given ID.
// Iterates over a linked list of entity handles; for each handle whose
// associated entity has ID at +0x2B4 matching the specified ID, sets the
// flag at +0x298 to the given value.

int __thiscall EntityManager::setFlagById(int thisPtr, int targetId, char flagVal)
{
  int listHead; // from this + 0x8
  int currentNode; // current node in list traversal
  int nextNode; // next node pointer (used for termination check)

  if (targetId == 0) {
    return 0;
  }

  listHead = *(int *)(thisPtr + 8);
  // Read the next pointer from the list head to start traversal
  currentNode = **(int **)(listHead + 0x1c);

  while (true) {
    // Re-fetch the head's next pointer each iteration (sentinel anchor)
    int headNext = *(int *)(*(int *)(thisPtr + 8) + 0x1c);
    if ((currentNode == 0) || (currentNode != *(int *)(thisPtr + 8))) {
      // Possible safety check for invalid list structure
      FUN_00b97aea(); // likely assertion or debug break
    }
    if (currentNode == headNext) {
      break; // reached the sentinel (end of list)
    }
    if (currentNode == 0) {
      FUN_00b97aea();
    }
    if (currentNode == *(int *)(currentNode + 0x1c)) {
      FUN_00b97aea();
    }
    // Check if the entity's ID matches
    int entityPtr = *(int *)(currentNode + 0x10); // +0x10: pointer to associated entity
    if (*(int *)(entityPtr + 0x2b4) == targetId) {
      if (currentNode == *(int *)(currentNode + 0x1c)) {
        FUN_00b97aea();
      }
      *(char *)(entityPtr + 0x298) = flagVal; // +0x298: flag byte (0 or 1)
    }
    // Advance to next node
    FUN_005e09e0(); // iterator function, updates currentNode and maybe nextNode
  }
  return 1;
}