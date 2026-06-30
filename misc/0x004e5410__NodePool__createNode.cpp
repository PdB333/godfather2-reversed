// FUNC_NAME: NodePool::createNode
void NodePool::createNode(uint key, undefined4 param2, undefined4 param3, int param4, undefined4 param5,
                          undefined4 param6, undefined4 param7, undefined4 param8, undefined4 param9,
                          undefined4 param10)
{
  int allocResult;
  int newNodePtr;
  int *childHeadPtr;
  HashEntry entry;
  int valuePtr;

  entry.type = 2;          // +0x00? Actually local_18[1]=2, so entry.field1=2? Let's assign structure: HashEntry { uint key; uint type; uint size; uint flags; }
  entry.size = 0x10;       // local_18[2]
  entry.flags = 0;         // local_18[3]

  allocResult = allocObject(0xa0, &entry); // FUN_009c8ed0, allocates 0xa0 bytes with metadata
  if (allocResult == 0) {
    newNodePtr = 0;
  } else {
    newNodePtr = initNode(param2, param5, param6, param7, param8, param9, param10); // FUN_004e4e50
  }

  entry.key = key;         // local_18[0] = param1
  valuePtr = newNodePtr;   // local_1c = newNodePtr

  insertIntoHashTable(&entry, &valuePtr, key % *(uint *)(*(int *)(g_globalHashTable + 8) + 8)); // FUN_00423cf0

  if (param4 != 0) {
    int parentNode = getNodeFromId(param4); // FUN_0040add0
    int *childListPtr;
    if (parentNode == 0) {
      childListPtr = 0;
    } else {
      childListPtr = (int *)(parentNode + 4); // some field offset +4 in parent
    }

    childHeadPtr = (int *)(newNodePtr + 0x90); // +0x90: pointer to child list head
    if (*childHeadPtr != childListPtr) {
      if (*childHeadPtr != 0) {
        releaseChildList(childHeadPtr); // FUN_004daf90
      }
      *childHeadPtr = childListPtr;
      if (childListPtr != 0) {
        *(int *)(newNodePtr + 0x94) = *(int *)(childListPtr + 4); // +0x94: prev pointer? or next?
        *(int **)(childListPtr + 4) = childHeadPtr;               // link parent's child list
      }
    }
  }
  return;
}