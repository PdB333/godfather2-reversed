// FUNC_NAME: TwoLevelSortedPool::findOrAllocateNode
uint* __thiscall TwoLevelSortedPool::findOrAllocateNode(int thisPtr, char keepFlag)
{
  // This function manages a two-level sorted linked list (by two keys).
  // +0x24: head of first-level list (sorted by key1)
  // +0x2C: head of free list for node reuse
  // The key pair is passed via EAX register (pointer to two uint32s).
  // Internal nodes have fields:
  //   [0]: key
  //   [1]: next  (in current list)
  //   [2]: prev  (in current list)
  //   [3]: child (for level1) or value (for level2)

  uint* keyPair = (uint*)eax;  // implicit parameter: pointer to {key1, key2}

  uint* level1Node = *(uint**)(thisPtr + 0x24);
  if (level1Node != 0) {
    // Search first-level list by key1
    while (*level1Node < *keyPair) {
      level1Node = (uint*)level1Node[1];
      if (level1Node == 0) {
        return 0;
      }
    }
    if (*level1Node == *keyPair) {
      uint* level2Node = (uint*)level1Node[3]; // child list head
      if (level2Node != 0) {
        // Search second-level list by key2
        while (*level2Node < keyPair[1]) {
          level2Node = (uint*)level2Node[1];
          if (level2Node == 0) {
            return 0;
          }
        }
        if (*level2Node == keyPair[1]) {
          uint* valuePtr = level2Node + 3; // pointer to the value field

          int newNode = FUN_004c46d0(); // allocate a node from pool
          if (newNode != 0) {
            // Detach newNode from its original list and attach to free list (thisPtr+0x2C)
            if (*(int*)(newNode + 8) == 0) {
              *valuePtr = *(uint*)(newNode + 4);
            } else {
              *(uint*)(*(int*)(newNode + 8) + 4) = *(uint*)(newNode + 4);
            }
            if (*(int*)(newNode + 4) != 0) {
              *(uint*)(*(int*)(newNode + 4) + 8) = *(uint*)(newNode + 8);
            }
            *(uint*)(newNode + 4) = *(uint*)(thisPtr + 0x2C);
            *(int*)(thisPtr + 0x2C) = newNode;

            if (keepFlag != '\0') {
              return valuePtr;
            }

            // If keepFlag is false, remove level2Node and level1Node and push them to free list
            if (*valuePtr == 0) {
              if (level2Node[2] == 0) {
                level1Node[3] = level2Node[1];
              } else {
                *(uint*)(level2Node[2] + 4) = level2Node[1];
              }
              if (level2Node[1] != 0) {
                *(uint*)(level2Node[1] + 8) = level2Node[2];
              }
              level2Node[1] = *(uint*)(thisPtr + 0x2C);
              *(uint**)(thisPtr + 0x2C) = level2Node;
            }

            if (level1Node[3] == 0) {
              if (level1Node[2] == 0) {
                *(uint*)(thisPtr + 0x24) = level1Node[1];
              } else {
                *(uint*)(level1Node[2] + 4) = level1Node[1];
              }
              if (level1Node[1] != 0) {
                *(uint*)(level1Node[1] + 8) = level1Node[2];
              }
              level1Node[1] = *(uint*)(thisPtr + 0x2C);
              *(uint**)(thisPtr + 0x2C) = level1Node;
            }
          }
          return 0;
        }
      }
      return 0;
    }
  }
  return 0;
}