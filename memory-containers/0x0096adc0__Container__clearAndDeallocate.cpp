// FUNC_NAME: Container::clearAndDeallocate
void __fastcall Container::clearAndDeallocate(int *thisPtr)
{
    // thisPtr points to a container object with layout:
    // +0x00: int* bucketArray      (pointer to bucket array structure)
    // +0x04: int  size             (set to 0 at end)
    // +0x08: int  bucketCount      (number of buckets)
    // +0x10: int  elementCount     (decremented as nodes are freed)
    int *nextNodePtr;
    int *currentNodePtr;
    uint bucketIndex;

    // Get first head pointer from bucketArray->heads (offset +0x08)
    currentNodePtr = **(int ***)(*(int **)(*thisPtr + 8) + 0); // double deref for head

    while (currentNodePtr != (int *)0x0) {
        // Save next node pointer from node->next (offset +0x08)
        nextNodePtr = **(int ***)(currentNodePtr + 8);
        // Destroy the element stored in the node (pointer at node+0x08? Actually same as next field? No, the argument is *(int **)(currentNodePtr+8) which is the element pointer)
        FUN_009c8f10(*(int **)(currentNodePtr + 8)); // destroyElement
        // Destroy the node itself
        FUN_009c8eb0(currentNodePtr); // destroyNode
        // Decrement element count
        thisPtr[4] = thisPtr[4] + -1;
        currentNodePtr = nextNodePtr;
    }

    // Zero out all bucket heads in the bucket array
    bucketIndex = 0;
    do {
        *(undefined4 *)(*(int *)(*thisPtr + 8) + bucketIndex * 4) = 0;
        bucketIndex = bucketIndex + 1;
    } while (bucketIndex <= (uint)thisPtr[2]);

    // Reset size to 0
    thisPtr[1] = 0;
    return;
}