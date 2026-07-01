// FUNC_NAME: PacketQueueManager::setNextNode
void __thiscall PacketQueueManager::setNextNode(PacketQueueManager* this, ListNodeContainer* container) {
    // 'this' points to a PacketQueueManager object
    // At offset 0x58: pointer to a sub-manager (StreamManager or similar)
    StreamManager* streamMgr = *(StreamManager**)((char*)this + 0x58);
    
    // Pointer to the head/tail node pointer in the stream manager at offset 0x24bc
    int** nodePtr = (int**)((char*)streamMgr + 0x24bc);
    
    // The container may be null; if non-null, adjust to point to the actual node (+0x48)
    ListNode* node = (container != nullptr) ? (ListNode*)((char*)container + 0x48) : nullptr;
    
    if (*nodePtr != node) {
        // Remove the old node if it existed
        if (*nodePtr != nullptr) {
            removeNode(nodePtr);  // FUN_004daf90 - removes the node from the list
        }
        *nodePtr = node;
        if (node != nullptr) {
            // Update the "prev" pointer of the new node (at offset 0x04) to point back to nodePtr
            *(int**)((char*)node + 0x04) = nodePtr;
            // Also copy the node's value at +0x04 to stream manager's +0x24c0 (synchronization)
            *(int*)((char*)streamMgr + 0x24c0) = *(int*)((char*)node + 0x04);
        }
    }
}