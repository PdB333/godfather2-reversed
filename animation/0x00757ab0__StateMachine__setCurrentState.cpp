// FUNC_NAME: StateMachine::setCurrentState
void __thiscall StateMachine::setCurrentState(StateMachine *this, StateNode *srcNode)
{
  // +0xC0: m_pCurrentState (pointer to a StateNode)
  // +0xC4: m_pOldPrev (backup of prev pointer during swap)
  // +0xC8: m_idCopy (8 bytes, 2 ints from srcNode+2)
  // +0xD0: m_fieldD0 (int from srcNode+4)
  // +0xD4: m_fieldD4 (char from srcNode+5)

  StateNode **ppCurrent = (StateNode **)((char *)this + 0xC0);
  StateNode *pOld = *ppCurrent;

  if (pOld != srcNode)
  {
    int newId = *(int *)srcNode; // srcNode->id at offset 0
    // Only change if the old node doesn't exist or has a different ID
    if (pOld == nullptr || *(int *)pOld != newId)
    {
      if (pOld != nullptr)
      {
        // Cleanup the old node (likely destructor or unlink)
        FUN_004daf90(pOld);
      }
      *ppCurrent = srcNode;
      if (srcNode != nullptr)
      {
        // Backup srcNode's previous pointer, then set it to point back to the
        // member variable location (creating a back-link to the container)
        *(StateNode **)((char *)this + 0xC4) = *(StateNode **)((char *)srcNode + 4);
        *(StateNode ***)((char *)srcNode + 4) = ppCurrent;
      }
    }
  }

  // Copy bulk data from the source node
  *(uint64_t *)((char *)this + 0xC8) = *(uint64_t *)((int *)srcNode + 2);
  *(int *)((char *)this + 0xD0) = ((int *)srcNode)[4];
  *(char *)((char *)this + 0xD4) = (char)((int *)srcNode)[5];
}