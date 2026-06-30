// FUNC_NAME: LinkedList::detachRange
void LinkedList::detachRange(int *outResult, Node *startNode, Node *endNode, Node *headSentinel, Node *tailSentinel)
{
    // this+0x1c: pointer to the head sentinel node (m_head)
    Node *headSentinelValue = **(Node ***)(this + 0x1c); // Dereference to get the stored value (probably the sentinel's self-pointer or data)
    // Assertion: startNode must be null or equal to this (the list container) – likely an assertion that the node belongs to this list
    if ((startNode != nullptr) && (startNode != (Node *)this)) {
        FUN_00b97aea(); // assertion failure
    }

    // Special case: if endNode matches the value stored in the head sentinel (i.e., the list is empty or endNode is the sentinel itself)
    if (endNode == headSentinelValue) {
        Node *headNode = *(Node **)(this + 0x1c);
        // Assertion: headSentinel must be null or equal to this (same as above)
        if ((headSentinel != nullptr) && (headSentinel != (Node *)this)) {
            FUN_00b97aea();
        }
        // tailSentinel must match the head sentinel's stored value
        if (tailSentinel == headSentinelValue) {
            // Call a function that takes the data field at offset +0x4 (maybe a destructor or cleanup)
            FUN_005e1400(*(undefined4 *)(headNode + 4));
            // Reset the list to a single-node circular state:
            // Set node+4 to point to itself (self-reference)
            *(Node **)(headNode + 4) = headNode;
            // Set node+0 (prev?) to point to itself
            *(Node **)(headNode + 0) = headNode;
            // Set node+8 (next?) to point to itself
            *(Node **)(headNode + 8) = headNode;
            // output: outResult[1] = the head sentinel's stored value (now the node itself)
            outResult[1] = (int)headNode;
            // output: outResult[0] = this (list container)
            outResult[0] = (int)this;
            return;
        }
    }

    // Loop to traverse the range until endNode equals tailSentinel
    while (true) {
        // Assertion: startNode must be null or equal to headSentinel (i.e., the range starts at the head)
        if ((startNode != nullptr) && (startNode != headSentinel)) {
            FUN_00b97aea();
        }
        if (endNode == tailSentinel) break;
        // Step to next node in the range
        FUN_005e15c0();
        // Perform a transfer operation on the current node pair
        FUN_005e0c80(this, (undefined1 (*) [8])temp, startNode, endNode);
    }

    // Return the detached range: first node and last node
    outResult[1] = (int)endNode;
    outResult[0] = (int)startNode;
}