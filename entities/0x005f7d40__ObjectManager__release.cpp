// FUNC_NAME: ObjectManager::release
void __thiscall ObjectManager::release(int this, void* object) {
    // Temporary node for list removal (unused result)
    ListNode tempNode;
    
    // Circular linked list of all managed nodes at this + 0x6c
    ListNode* headNode = (ListNode*)(this + 0x6c);
    
    // Iterate over all nodes until we find the one containing 'object'
    ListNode* curNode = headNode->next;
    while (curNode != headNode) {
        // Debug assertion: detect invalid circular iteration
        if (curNode == headNode) {
            FUN_00b97aea(); // assert(0)
        }
        
        // Each node's third field (offset 8) holds the object pointer
        if (curNode->object == object) {
            // Remove this node from the active list at this + 0x54
            FUN_005f92d0(&tempNode, (int)(this + 0x54), curNode);
            break;
        }
        
        if (curNode == headNode) {
            FUN_00b97aea(); // assert(0)
        }
        curNode = curNode->next;
    }
    
    // Call the object's virtual release method (vtable[0])(0)
    (*(void (**)(int))(*(int*)object))(0);
    
    // Now return the object to the global memory pool
    // unaff_EBX is a global pointer to the memory pool structure
    MemoryPool* pool = (MemoryPool*)unaff_EBX;
    FreeListNode* freeListHead = (FreeListNode*)pool->freeList; // offset 0x28
    
    if (freeListHead != nullptr) {
        FreeListNode* firstFree = (FreeListNode*)freeListHead->next;
        
        // If the pool is not empty, check that object lies within its allocated range
        if ((firstFree != nullptr) && 
            (object < (void*)((int)firstFree + freeListHead->size)) &&
            (object >= firstFree)) {
            // Call object's destructor? (vtable[2])(object)
            (*(void (**)(void*))(*(int*)freeListHead->destructorVtable + 8))(object);
            return;
        }
        
        // Push object onto the free list (front insertion)
        *(void**)object = freeListHead->next;    // object->next = freeListHead->next
        freeListHead->count++;                   // increment free count
        freeListHead->next = object;             // freeListHead->next = object
    }
}