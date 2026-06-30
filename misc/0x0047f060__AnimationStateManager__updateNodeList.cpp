// FUNC_NAME: AnimationStateManager::updateNodeList

void __fastcall AnimationStateManager::updateNodeList(void)
{
    int *pListHead = reinterpret_cast<int *>(this + 0x70);  // +0x70: pointer to head of linked list
    if (*pListHead == 0) {
        int iNewNode = getNodeFromPool(this + 0x60);  // +0x60: key or ID for lookup
        if (*pListHead != iNewNode) {
            if (*pListHead != 0) {
                removeNodeFromList(pListHead);  // remove old head
            }
            *pListHead = iNewNode;
            if (iNewNode != 0) {
                // Update linked list pointers: store previous head pointer at +0x74
                *(reinterpret_cast<int *>(this + 0x74)) = *(reinterpret_cast<int *>(iNewNode + 4));  // +0x74: previous list head pointer
                // Set node's forward pointer to point back to the list head variable
                *reinterpret_cast<int **>(iNewNode + 4) = pListHead;
            }
        }
    }
    if (*pListHead != 0) {
        if (*(char *)(this + 0x78) != '\0') {
            char bResult = evaluateState(0, *(char *)(this + 0x79) != '\0');  // +0x78, +0x79: flags
            *(char *)(this + 0x7a) = bResult;  // +0x7a: result byte
            return;
        }
        char bResult = evaluateState(1, 0);
        *(char *)(this + 0x7a) = bResult;
    }
}