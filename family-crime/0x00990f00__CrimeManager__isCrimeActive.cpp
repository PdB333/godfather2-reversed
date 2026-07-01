// FUNC_NAME: CrimeManager::isCrimeActive
undefined4 __thiscall CrimeManager::isCrimeActive(CrimeManager *this, undefined4 param_2, uint crimeId)
{
  CrimeNode *currentNode;
  CrimeNode *headNode;
  undefined4 result;
  
  headNode = *(CrimeNode **)(this + 0x60);  // +0x60: head of crime linked list
  result = 2;  // default: not active
  if (headNode != 0) {
    // Traverse the singly linked list (each node has next pointer at +0x04)
    while (currentNode->crimeId != (ushort)crimeId) {  // +0x44: crime ID (short)
      if (crimeId < (uint)(ushort)currentNode->crimeId) {
        return 2;  // not found (past insertion point)
      }
      currentNode = *(CrimeNode **)(currentNode + 4);  // +0x04: next node pointer
      if (currentNode == 0) {
        return 2;  // end of list, not found
      }
    }
    // Node found; increment crimeId to check next sequential ID availability
    crimeId = crimeId + 1;
    // sub_5bccb0 likely checks if the next crimeId exists or is valid
    if ((FUN_005bccb0(&crimeId) != 0) ||
        (*(int *)(currentNode + 0x38) != 0) ||   // +0x38: some flag/pointer (e.g., active state)
        (*(int *)(currentNode + 0x3c) != 0)) {   // +0x3c: another flag/pointer
      result = 0;  // crime is active
    }
  }
  return result;
}