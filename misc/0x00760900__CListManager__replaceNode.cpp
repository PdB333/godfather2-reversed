// FUNC_NAME: CListManager::replaceNode
void __thiscall CListManager::replaceNode(int this, int *newNode)
{
  int *pCurrentNodePtr; // pointer to m_pCurrentNode field at this+0x68
  int currentNode;      // current node pointer (or null)
  int newNodePtr;       // new node pointer (first field of new entry)

  pCurrentNodePtr = (int *)(this + 0x68); // +0x68: pointer to current node (Node*)
  if (pCurrentNodePtr == newNode) {
    *(int *)(this + 0x70) = newNode[2]; // +0x70: data field
    return;
  }
  newNodePtr = *newNode; // first field of new entry is the node pointer itself
  if (*pCurrentNodePtr != newNodePtr) {
    if (*pCurrentNodePtr != 0) {
      FUN_004daf90(pCurrentNodePtr); // cleanup/release old node
    }
    *pCurrentNodePtr = newNodePtr; // store new node pointer
    if (newNodePtr != 0) {
      // Update back-pointer: newNode[1] (at offset 4) was previously pointing to where it was stored
      // Now set it to point to this manager's m_pCurrentNode field
      *(int *)(this + 0x6c) = *(int *)(newNodePtr + 4); // +0x6c: presumably previous back-pointer
      *(int **)(newNodePtr + 4) = pCurrentNodePtr;     // back-pointer now points to manager's field
      *(int *)(this + 0x70) = newNode[2];              // copy data field
      return;
    }
    *(int *)(this + 0x70) = newNode[2];
    return;
  }
  *(int *)(this + 0x70) = newNode[2];
  return;
}