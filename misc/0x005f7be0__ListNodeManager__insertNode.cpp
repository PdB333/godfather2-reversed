// FUNC_NAME: ListNodeManager::insertNode
int __thiscall ListNodeManager::insertNode(int param_2) // param_2 is likely the data/key for the node
{
    int allocResult;        // local_4, success code from allocator
    int nodeKey = 0;        // local_10, key from getFreeNode
    int nodeId;             // iVar3, returned node index/ID

    // Try to get a free node ID from the pool
    nodeId = getFreeNode(param_2, &nodeKey); // FUN_005f79a0 returns non-zero if success
    if (nodeId != 0) {
        // Check if allocation is allowed (based on a flag in pool settings)
        if (*(int*)(*(int*)(this + 0x28) + 0x14) != 0) { // this->poolSettings->allowAllocation
            // Allocate a new node structure (likely 20 bytes)
            NodeStructure* newNode = (NodeStructure*)createNodeStructure(); // FUN_004abf10 allocates with vtable
            if (newNode != nullptr) {
                newNode[1] = 0;                         // node->next = nullptr
                newNode[0] = &PTR_FUN_00e407c8;        // vtable pointer
                newNode[2] = nodeId;                    // node->id = nodeId
                newNode[3] = nodeKey;                   // node->key = nodeKey
                newNode[4] = g_someGlobalVar;           // node->data = g_someGlobalVar
            }

            // Get head node of the list (from this->listHead)
            NodeStructure* headNode = *(NodeStructure**)(this + 0x6c); // +0x6c: head node pointer
            int headNext = *(int*)(headNode + 4); // head->next index/pointer

            // Determine the pointer to use as the "previous" pointer (may be dummy)
            int* prevPtr = *(int**)(this + 0x58); // +0x58: pointer to the sentinel's prev field
            if (prevPtr == nullptr) {
                int dummyPrev = 0;
                int dummyNext = 0;
                allocResult = 0;
                prevPtr = &dummyPrev; // point to local stack as dummy
            }

            // Call virtual allocator function to get space for the new node (0xc = 12 bytes?)
            int* allocSpace = (int*)(this->vtable->allocate(0xc, prevPtr)); // this->vtable[0] is allocator function
            if (allocSpace != nullptr) {
                *allocSpace = headNode;                           // allocSpace[0] = head node pointer
                allocSpace[1] = unaff_ESI;                        // allocSpace[1] = ESI (prev pointer of some node)
                allocSpace[2] = allocResult;                       // allocSpace[2] = alloc result code
            }

            postAllocation(); // FUN_005fa010: any post-alloc processing

            // Insert newNode into linked list
            // Update head->next to point to newNode
            *(NodeStructure**)(headNode + 4) = newNode;
            // Update the prev pointer (pointed to by unaff_ESI) to point to newNode
            *(NodeStructure**)*prevPtr = newNode; // *prevPtr should be address of sentinel's prev field

            return allocResult;
        }
        // If allocation is not allowed, free the previously obtained node ID
        freeNode(nodeId); // FUN_005f7e50
    }
    return 0; // failure
}