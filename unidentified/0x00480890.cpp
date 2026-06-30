// FUN_00480890: ObjectAllocator::attachToGlobalPool
void ObjectAllocator::attachToGlobalPool(void)
{
    // this is passed in ECX (in_EAX)
    PoolManager* pool = gPoolManager;                     // DAT_01223430
    if (((*(int*)(this + 0x5c) != 0) &&                   // check some object flag
         (pool != (PoolManager*)-0x14) &&                 // valid pool pointer
         (int allocSize = poolGetAllocSize(), allocSize != 0) &&
         (undefined4* newNode = (undefined4*)poolAllocNode(), newNode != nullptr)))
    {
        // Mark pool flags: +0x1c
        pool->flags |= 1;

        // Insert newNode at head of pool's linked list
        // +0x20 holds the current head pointer
        newNode[0] = (undefined4)pool->head;             // newNode->next = old head
        pool->head = newNode;                            // head = newNode

        newNode[4] = allocSize;                          // +0x10 store allocation size
        newNode[2] = gSomeGlobal;                        // +0x08 store global value (DAT_01205224)
    }
}