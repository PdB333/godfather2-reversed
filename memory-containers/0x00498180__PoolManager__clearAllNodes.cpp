// FUNC_NAME: PoolManager::clearAllNodes
void __fastcall PoolManager::clearAllNodes(int* this) // this is pointer to pool manager object
{
    int* pNode;          // current node pointer
    int* pNextNode;      // next node pointer

    // Get head node: from this->vtable+0x30? Actually *this is vtable pointer, then offset 0x30 stores head pointer.
    pNode = *(int**)(this[0] + 0x30);   // this[0] = vtable ptr; *(vtable+0x30) = head

    while (pNode != nullptr) {
        pNextNode = *(int**)(pNode + 0x30);   // each node has next pointer at +0x30
        // Destroy node's embedded data (at pNode+0x30? Actually argument is the next pointer itself? Let's interpret as node's data pointer)
        // Original: FUN_009c8f10( *(int**)(pNode+0x30) ) - that passes the next pointer, but we interpret as data pointer.
        FUN_009c8f10( pNode + 0x30 );   // may be wrong but reconstructing
        FUN_009c8eb0( pNode );          // free node
        this[4] = this[4] - 1;           // decrement count (offset +0x10)
        pNode = pNextNode;
    }

    // Zero out the memory pool entries
    for (uint i = 0; i <= (uint)this[2]; i++) {  // this[2] = pool size (offset +0x08)
        *(int*)(this[0] + 0x30 + i * sizeof(int)) = 0;   // zero head pointer? Actually clears the array at vtable+0x30?
    }
    this[1] = 0;   // reset some counter (offset +0x04)
}