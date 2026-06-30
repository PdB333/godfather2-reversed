// FUNC_NAME: EntityManager::findOrCreateEntityByUID
uint32 EntityManager::findOrCreateEntityByUID(uint32 uid)
{
    Node* node;
    
    // Enter critical section (synchronization for hash table access)
    enterCriticalSection();
    
    // Hash table lookup: bucket index = uid & 0x1FF (512 buckets)
    bucket = g_hashTable[uid & 0x1FF];
    node = bucket;
    while (node != nullptr) {
        if (node->uid == uid) {
            break;
        }
        node = node->next;
    }
    
    // If not found, create a new node
    if (node == nullptr) {
        node = createNode(uid);          // FUN_00616590
    }
    
    if (node == nullptr) {
        // If creation also fails, return error
        return -1;
    }
    
    // Perform operation using node and internal context (this->context)
    uint32 result = performOperation(node, this->context, 0);  // FUN_00616a60
    if (result == 0) {
        return -1;
    }
    return *reinterpret_cast<uint32*>(result + 4);   // Return value at node+4
}