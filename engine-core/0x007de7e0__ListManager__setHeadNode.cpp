// FUNC_NAME: ListManager::setHeadNode
void __fastcall ListManager::setHeadNode(int thisPtr)
{
    int containerPtr;      // iVar2 - pointer to some container
    int dataPtr;           // iVar1 - pointer to a data structure from this
    int *headPtr;          // piVar3 - pointer to head node pointer

    containerPtr = GetGlobalContainer();          // FUN_00705820 - returns a container pointer
    dataPtr = *(int *)(thisPtr + 0x58);          // +0x58: m_pData (or m_pListOwner)
    headPtr = (int *)(dataPtr + 0x24b4);        // +0x24b4: head node pointer (list head)

    // The container has a node embedded at offset 0x48
    if (containerPtr == 0) {
        containerPtr = 0;
    } else {
        containerPtr = containerPtr + 0x48;       // +0x48: offset to node struct
    }

    // If head is different, replace it
    if (*headPtr != containerPtr) {
        if (*headPtr != 0) {
            RemoveNodeFromList(headPtr);          // FUN_004daf90 - likely unlink/remove old head
        }
        *headPtr = containerPtr;
        if (containerPtr != 0) {
            // Update the "next" pointer at +0x24b8 (maybe tail or next slot)
            *(int *)(dataPtr + 0x24b8) = *(int *)(containerPtr + 4);
            // Backlink: node's +4 points to the head pointer location
            *(int **)(containerPtr + 4) = headPtr;
        }
    }
}