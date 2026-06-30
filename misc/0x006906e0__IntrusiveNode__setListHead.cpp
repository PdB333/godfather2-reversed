// FUNC_NAME: IntrusiveNode::setListHead
int* __thiscall IntrusiveNode::setListHead(int* this, int* pParent) {
    int* pListHead;
    if (pParent == (int*)0) {
        pListHead = (int*)0;
    } else {
        pListHead = (int*)((char*)pParent + 0x48); // offset to list head object in parent
    }
    if (this[0] != (int)pListHead) { // m_pListHead
        if (this[0] != 0) {
            detachFromList(this); // FUN_004daf90 - remove from old list
        }
        this[0] = (int)pListHead; // set new list head
        if (pListHead != (int*)0) {
            // pListHead[1] is the next pointer at offset 4
            this[1] = *(int*)((char*)pListHead + 4); // m_pNext = old head's next
            *(int**)((char*)pListHead + 4) = this; // head->next = this
        }
    }
    return this;
}