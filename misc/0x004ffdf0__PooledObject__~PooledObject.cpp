// FUNC_NAME: PooledObject::~PooledObject
void __thiscall PooledObject::~PooledObject(PooledObject *this) {
    // Set vtable to derived class vtable (first)
    this->vtablePtr = &PTR_FUN_00e37bf0;
    
    // Call sub-object destructor at offset 0x24 (member of type BaseSubObject)
    FUN_0043e500(&this->subObject);
    
    // Thread-local storage handling: get a per-thread bit array and set a flag
    // TLS at FS:0x2c points to a structure; dereference twice to get base of bit array
    // then use field at offset 0x10 as index to set a bit (marking this slot as allocated/freed)
    uint *puFlagArray = *(uint **)(*(int *)(*(int **)(__readfsdword(0x2c) + 8) + 0) + 0);
    puFlagArray[this->m_field10] |= 1;
    
    // Remove this object from a linked list (node at offset 0x3c)
    int iNode = this->m_linkedListNode;
    if (iNode != 0) {
        Undefined4 *pPrevNode = *(Undefined4 **)(iNode + 4);
        if (pPrevNode == &this->m_linkedListNode) {
            // Node was head of list; update head to next
            *(Undefined4 *)(iNode + 4) = this->m_nextNode;
        } else {
            // Search backwards to find the node pointing to this
            Undefined4 *pCurr = pPrevNode;
            Undefined4 *pNext = (Undefined4 *)pPrevNode[1];
            while (pNext != &this->m_linkedListNode) {
                pCurr = (Undefined4 *)pCurr[1];
                pNext = (Undefined4 *)pCurr[1];
            }
            pCurr[1] = this->m_nextNode;
        }
    }
    
    // Change vtable to base class vtable (second)
    this->vtablePtr = &PTR_FUN_00e37110;
    
    // If field at offset 0x10 is non-zero, add it to a global free list
    int iField = this->m_field10;
    if (iField != 0) {
        // Global manager at DAT_01206880, at offset 0x14 is a pointer to a list builder
        int **ppFreeList = (int **)(DAT_01206880 + 0x14);
        // Set first element of current list node to a vtable (type info)
        **(Undefined4 **)*ppFreeList = &PTR_LAB_01123be8;
        // Advance pointer by 4 bytes
        *ppFreeList = (int *)((char *)*ppFreeList + 4);
        // Write our field value (the object's identifier/pointer) as next element
        *(int *)*ppFreeList = iField;
        // Advance again (move to next free slot)
        *ppFreeList = (int *)((char *)*ppFreeList + 4);
    }
}