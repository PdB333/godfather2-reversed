// FUNC_NAME: LinkNode::attachToParentNode
int* __thiscall LinkNode::attachToParentNode(int* thisPtr, int* parentObj) {
    int* targetNode; // pointer to the embedded node in the parent at +0x48

    if (parentObj == nullptr) {
        targetNode = nullptr;
    } else {
        targetNode = parentObj + 0x48; // parent's embedded node (offset +0x48)
    }

    // Only change if we are not already attached to the same node
    if (thisPtr[0] != targetNode) {
        // Detach from current list if attached
        if (thisPtr[0] != nullptr) {
            FUN_004daf90(thisPtr); // remove node from current doubly linked list
        }

        // Store the new previous node (target)
        thisPtr[0] = targetNode;

        if (targetNode != nullptr) {
            // Insert this node after targetNode in the list
            thisPtr[1] = targetNode[1];     // this->next = target->next  (offset +4)
            targetNode[1] = thisPtr;        // target->next = this
        }
    }

    return thisPtr;
}