// FUN_0078cfd0: LinkedListNode::insertBefore(SomeParentClass* parentWithNodeAtOffset48)
int* __thiscall LinkedListNode::insertBefore(int* this, int parentObjWithNode)
{
    // parentObjWithNode is a pointer to an object that contains an embedded LinkedListNode at offset +0x48
    int* targetNode;
    if (parentObjWithNode == 0) {
        targetNode = 0;
    } else {
        targetNode = (int*)(parentObjWithNode + 0x48); // extract the embedded node pointer
    }

    // If this node is not already before targetNode, unlink it from its current list and insert before targetNode
    if (this[0] != targetNode) {
        if (this[0] != 0) {
            FUN_004daf90(this); // remove this from its current list
        }
        this[0] = targetNode;                        // this->next = targetNode
        this[1] = *(int*)(targetNode + 4);           // this->prev = targetNode->prev
        *(int**)(targetNode + 4) = this;             // targetNode->prev = this
        // Note: missing update of targetNode->prev->next (which would be set to this).
        // This suggests targetNode is always the head of the list or a special sentinel.
    }
    return this;
}