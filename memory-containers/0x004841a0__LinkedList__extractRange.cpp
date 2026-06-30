// FUNC_NAME: LinkedList::extractRange
void LinkedList::extractRange(int* outFirstLast,
                              int* listA,  // +0x00 pointer to list object (must be null or 'this')
                              int* nodeA,  // +0x04 node/sentinel within listA
                              int* listB,  // +0x08 pointer to list object (must be null or 'this')
                              int* nodeB)  // +0x0C node/sentinel within listB
{
    // The list object layout:
    // +0x00: head pointer (Node*)
    // +0x04: tail? Actually a pointer to a pointer? We'll treat as Node**
    // +0x08: size or count

    // Dereference head->head to get the first node's raw value (usually the sentinel's data)
    int sentinelData = *(int*)*(int*)(this + 4); // iVar1

    // Ensure that if listA is non‑null it points to 'this' (safety check)
    if ((listA != 0) && (listA != this)) {
        FUN_00b97aea(); // assertion failure
    }

    if (nodeA == sentinelData) {
        sentinelData = *(int*)(this + 4); // reload the head pointer (not its data)

        // Same safety check for listB
        if ((listB != 0) && (listB != this)) {
            FUN_00b97aea();
        }

        if (nodeB == sentinelData) {
            // Special case: both nodeA and nodeB equal the first node.
            // This means we are extracting the entire list (only one node?).
            // Unlink the first node from the list (removes it).
            FUN_00484d80(*(int*)(*(int*)(this + 4) + 4)); // e.g., free the next pointer

            // Rewire the list head to point to itself (circular empty list)
            *(int*)(*(int*)(this + 4) + 4) = *(int*)(this + 4); // node->next = head
            *(int*)(this + 8) = 0;                             // size = 0
            *(int*)*(int*)(this + 4) = *(int*)(this + 4);     // node->prev = head
            *(int*)(*(int*)(this + 4) + 8) = *(int*)(this + 4); // node->data = head? (likely sentinel reset)

            // Output: return the list pointer and the data/sentinel of the extracted node
            outFirstLast[1] = **(int**)(this + 4); // extracted node's data (or pointer)
            outFirstLast[0] = this;
            return;
        }
    }

    // Normal case: iterate until nodeA == nodeB (i.e., we have walked the range)
    while (true) {
        // Assert listA and listB are the same list (or listA is null)
        if ((listA != 0) && (listA != listB)) {
            FUN_00b97aea();
        }

        if (nodeA == nodeB) {
            break;
        }

        // Advance to the next element
        FUN_00484fb0(); // likely a no‑op or global iterator advance
        FUN_00484770(this, local_8, listA, nodeA); // updates nodeA to next node via local_8 buffer
    }

    outFirstLast[1] = nodeA;
    outFirstLast[0] = listA;
}