// FUNC_NAME: DataStruct::findEntryOrBounds
void DataStruct::findEntryOrBounds(uint *key)
{
  undefined4 *currentNode;
  undefined4 *nextNode;
  undefined4 *parentNode;
  int thisPtr;
  
  parentNode = *(undefined4 **)(thisPtr + 0x1c); // +0x1c: tree root node pointer
  if (*(char *)((int)parentNode[1] + 0x15) == '\0') { // +0x15: flag indicating leaf node? (0 = internal)
    currentNode = (undefined4 *)parentNode[1]; // +0x4: left child or parent for sentinel
    do {
      if ((uint)currentNode[3] < *key) { // +0xc: node key value
        nextNode = (undefined4 *)currentNode[2]; // +0x8: right child
      }
      else {
        nextNode = (undefined4 *)*currentNode; // +0x0: left child
        parentNode = currentNode;
      }
      currentNode = nextNode;
    } while (*(char *)((int)nextNode + 0x15) == '\0'); // check if leaf node
  }
  
  currentNode = *(undefined4 **)(thisPtr + 0x1c); // re-fetch root
  if ((parentNode != currentNode) && ((uint)parentNode[3] <= *key)) {
    *in_EAX = thisPtr;
    in_EAX[1] = (int)parentNode; // node found or exact match
    return;
  }
  
  *in_EAX = thisPtr;
  in_EAX[1] = (int)currentNode; // no match, return root/bounds
  return;
}