// FUNC_NAME: NodeListManager::setActiveNode
void __thiscall NodeListManager::setActiveNode(int this, int object) {
    int *headPtr = (int *)(this + 0x98); // pointer to head node (offset +0x98)
    // object is a container with an embedded node at offset 0x48
    int newNode = object;
    if (object == 0) {
        newNode = 0;
    } else {
        newNode = object + 0x48;
    }
    if (*headPtr != newNode) {
        if (*headPtr != 0) {
            releaseNode(headPtr); // FUN_004daf90: remove old head
        }
        *headPtr = newNode;
        if (newNode != 0) {
            // +0x9c stores the previous 'prev' pointer of the new node
            *(int *)(this + 0x9c) = *(int *)(newNode + 4);
            // set new node's prev pointer to point to headPtr
            *(int **)(newNode + 4) = headPtr;
        }
    }
    // decrement some counter at +0xa8 (maybe reference count)
    *(char *)(this + 0xa8) = *(char *)(this + 0xa8) - 1;
}