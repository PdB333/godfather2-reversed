// FUNC_NAME: Player::setCurrentNode
void __thiscall Player::setCurrentNode(void* this, void* newNode) {
    int** currentNodePtr = (int**)((char*)this + 0x3104); // pointer to current node
    void* adjustedNode = (newNode == nullptr) ? nullptr : (char*)newNode + 0x48; // node is at offset 0x48 from parameter

    if (*currentNodePtr == adjustedNode) {
        *(int*)((char*)this + 0x310C) = DAT_01205224; // set some timestamp/version
        return;
    }

    if (*currentNodePtr != nullptr) {
        FUN_004daf90(currentNodePtr); // remove old node from list
    }

    *currentNodePtr = adjustedNode; // set new current node

    if (adjustedNode != nullptr) {
        // Save the old next pointer of the new node into this->nextNode (offset 0x3108)
        *(int*)((char*)this + 0x3108) = *(int*)((char*)adjustedNode + 4);
        // Set the new node's prev pointer to point to this->currentNodePtr
        *(int**)((char*)adjustedNode + 4) = currentNodePtr;
        *(int*)((char*)this + 0x310C) = DAT_01205224;
        return;
    }

    *(int*)((char*)this + 0x310C) = DAT_01205224;
    return;
}