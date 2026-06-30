// FUNC_NAME: EARSListLink::setNextNode
void __thiscall EARSListLink::setNextNode(void* pNewNodeOwner) {
    int** ppNext = reinterpret_cast<int**>(this + 0x10);  // pointer to m_pNextNode
    int* pNewNode = nullptr;
    if (pNewNodeOwner != nullptr) {
        pNewNode = reinterpret_cast<int*>(reinterpret_cast<char*>(pNewNodeOwner) + 0x48);  // embedded node offset
    }
    if (*ppNext != pNewNode) {
        if (*ppNext != nullptr) {
            FUN_004daf90(ppNext);  // detach current next node
        }
        *ppNext = pNewNode;
        if (pNewNode != nullptr) {
            // update this node's prev pointer (m_ppPrevNext at +0x14)
            *(reinterpret_cast<int**>(this + 0x14)) = *reinterpret_cast<int**>(pNewNode + 4);
            // set new node's prev to address of this node's next pointer
            *reinterpret_cast<int***>(pNewNode + 4) = ppNext;
        }
    }
}