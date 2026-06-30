// FUNC_NAME: ListLinkNode::setValue
int* __thiscall ListLinkNode::setValue(int* thisNode, int newValue) {
    // Check if the current value differs from the new one
    if (*thisNode != newValue) {
        // If there was a previous value, detach from its back-pointer
        if (*thisNode != 0) {
            // Remove this node from the linked list (detach back-pointer)
            ListLinkNode::removeFromList(thisNode);
        }
        // Store the new value at offset 0 (the node's data pointer)
        *thisNode = newValue;
        // If new value is non-zero, set its back-pointer (offset +4) to point to this node
        if (newValue != 0) {
            // Save the old back-pointer from newValue into this node's next field (offset +4)
            thisNode[1] = *(int*)(newValue + 4);
            // Update newValue's back-pointer to this node
            *(int**)(newValue + 4) = thisNode;
        }
    }
    // Return this node for chaining
    return thisNode;
}