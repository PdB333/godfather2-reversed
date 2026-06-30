// FUNC_NAME: ObjectList::setHeadNode
void __thiscall ObjectList::setHeadNode(void* pObject) {
    int* pHead = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x54); // +0x54: head pointer
    int* pNode = nullptr;
    if (pObject != nullptr) {
        // Embedded list node at +0x48 within the object
        pNode = reinterpret_cast<int*>(reinterpret_cast<char*>(pObject) + 0x48);
    }
    if (*pHead != pNode) {
        // Remove old head node if present
        if (*pHead != nullptr) {
            // FUN_004daf90 - unlinks the node at *pHead from the list
            removeNode(pHead);
        }
        *pHead = pNode; // Set new head
        if (pNode != nullptr) {
            // Save the old prev pointer of the node (offset +4) into +0x58
            *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x58)) = *(pNode + 1);
            // Update the node's prev to point back to the head pointer (for easy removal)
            *(pNode + 1) = reinterpret_cast<int>(pHead);
        }
    }
}