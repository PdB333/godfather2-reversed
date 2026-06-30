// FUNC_NAME: SimSetLinkNode::getCurrentValue
int SimSetLinkNode::getCurrentValue(void)
{
    // +0x08: pointer to linked list head node (mHead)
    Node* head = *reinterpret_cast<Node**>(reinterpret_cast<char*>(this) + 0x08);
    if (head != nullptr) {
        // Initializes two local pointers: firstNode (mFirst) and currentNode (mCurrent)
        // The helper likely sets these from a stack-allocated iterator state
        Node* firstNode;  // local_10
        Node* currentNode; // local_c
        FUN_005def60(&firstNode); // probably sets firstNode and currentNode

        // +0x1c: field (mTail or mCount?) from head node
        Node* tail = *reinterpret_cast<Node**>(reinterpret_cast<char*>(head) + 0x1c);
        if (firstNode == nullptr || firstNode != head) {
            FUN_00b97aea(); // assert failure
        }
        if (currentNode != tail) {
            if (firstNode == nullptr) {
                FUN_00b97aea();
            }
            // +0x1c from firstNode: presumably same tail pointer
            if (currentNode == *reinterpret_cast<Node**>(reinterpret_cast<char*>(firstNode) + 0x1c)) {
                FUN_00b97aea();
            }
            // +0x10: the actual stored value (mValue)
            return *reinterpret_cast<int*>(reinterpret_cast<char*>(currentNode) + 0x10);
        }
    }
    return 0;
}