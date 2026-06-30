// FUNC_NAME: NetList::pruneByThreshold
int __thiscall NetList::pruneByThreshold(void* thisPtr, int threshold)
{
    int removedCount = 0;
    // Pointer to the current node pointer (initially points to the head pointer at offset 0 of this)
    ListNode** ppNode = (ListNode**)thisPtr;
    ListNode* currentNode = *ppNode;

    while (currentNode != nullptr)
    {
        // The byte at offset +5 holds a slot/sequence value; if threshold is less than it, keep the node
        if (threshold < (int)(unsigned int)(*(uint8_t*)((int)currentNode + 5)))
        {
            // Clear the lowest bit (flags: e.g., "in_use" or "pending")
            *(uint8_t*)((int)currentNode + 5) &= 0xFE;
            // Advance the pointer to point to the next field of the current node
            ppNode = &(currentNode->next);
        }
        else
        {
            // Unlink the node: set previous pointer to skip this node
            *ppNode = currentNode->next;
            removedCount++;
            destroyNode(currentNode); // FUN_00626ed0 - deallocate the node
        }
        currentNode = *ppNode;
    }
    return removedCount;
}