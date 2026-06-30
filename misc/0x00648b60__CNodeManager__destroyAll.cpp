// FUNC_NAME: CNodeManager::destroyAll
int CNodeManager::destroyAll(void)
{
  char *pCurNode;
  char *pChild;
  char *pNextChild;
  
  if (this->m_bActive != '\0') {
    this->m_bActive = '\0';
    this->preDestroy();
    pCurNode = this->m_pFirstNode;
    while (pCurNode != this + 4) {          // iterate until sentinel at offset +0x04
      pCurNode = this->m_pFirstNode;
      pChild = *(char **)(pCurNode + 0x10);  // child list head (offset +0x10)
      while (pChild != pCurNode) {
        pChild = *(char **)(pChild + 0x10);  // next child
        (this->m_pDestroyCallback)();        // callback at offset +0x190
      }
      // unlink node from its list (doubly linked at offsets +0x14 / +0x18)
      *(int *)(*(int *)(pCurNode + 0x14) + 0x18) = *(int *)(pCurNode + 0x18);
      *(int *)(*(int *)(pCurNode + 0x18) + 0x14) = *(int *)(pCurNode + 0x14);
      if (*(code **)(pCurNode + 0x20) != (code *)0x0) {
        (**(code **)(pCurNode + 0x20))();    // node-specific destructor at offset +0x20
      }
      if (pCurNode != this + 0x2c) {        // sentinel at offset +0x2c
        (this->m_pDestroyCallback)();
      }
      pCurNode = this->m_pFirstNode;
    }
  }
  if (this->m_pCriticalSection != NULL) {
    DeleteCriticalSection(this->m_pCriticalSection);
    memset(&this->m_pCriticalSection, 0, 4); // clear pointer region (offsets +0x1b8..+0x1bb)
  }
  return 1;
}