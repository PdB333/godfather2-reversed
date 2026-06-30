// FUNC_NAME: PoolAllocator::pushNode
void __fastcall PoolAllocator::pushNode(void* thisPtr, int eaxParam)
{
    // +0x18: pointer to pool descriptor (or list head)
    int poolBase = *(int*)((int)thisPtr + 0x18);
    // Allocate new node from the pool; second arg is current head->next
    int newNode = FUN_005fbfc0(poolBase, *(int*)(poolBase + 4), eaxParam);
    // Possibly update global allocation state
    FUN_005fc010();
    // Set head's next pointer to the new node
    *(int*)(poolBase + 4) = newNode;
    // Update the pointer that was stored at (newNode+4) to point to newNode
    // This likely adjusts the previous node's next to maintain list consistency
    *(int*)(*(int*)(newNode + 4)) = newNode;
    return;
}