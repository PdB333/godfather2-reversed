// FUNC_NAME: EARS::Trie::removeNode
void __thiscall EARS::Trie::removeNode(int *key)
{
    // Structure offsets (based on this pointer):
    // +0x00: root pointer (int*)
    // +0x04: depth (number of levels / branch slots)
    // +0x10: count of elements (size)
    // +0x14: parentPath array (stores ancestors during traversal)
    int depth = *(int*)((char*)this + 4); // unaff_EDI[1]
    int* current = *(int**)this;          // unaff_EDI[0] root

    int* lastVisited = 0;
    int* parentStack[32]; // placed on stack, corresponds to unaff_EDI[5] likely a local array

    // Traverse from highest depth slot down to 0
    while (depth >= 0)
    {
        // Access child at current slot index from current node
        int* child = *(int**)(current[2] + depth * 4); // piVar7
        if (child != 0)
        {
            int* nodePtr = child;
            do
            {
                lastVisited = nodePtr; // piVar6
                if (*key <= *nodePtr) break; // key comparison
                nodePtr = *(int**)(nodePtr[2] + depth * 4); // follow next node in same slot
                current = nodePtr; // piVar5
                child = nodePtr;
            } while (nodePtr != 0);
        }
        // Record the parent (or last valid node) for this slot
        parentStack[depth] = current; // stored at unaff_EDI[5] + 4 + depth*4
        depth--;
    }

    // If we found a node with matching key, remove it
    if ((lastVisited != 0) && (*lastVisited == *key))
    {
        unsigned int slot = 0;
        do
        {
            // Get the child array from parent node
            int* parentChildren = *(int**)(parentStack[slot] + 8); // iVar2
            // Check if the parent's child at this slot is exactly the node to remove
            if (*(int**)(parentChildren + slot * 4) != lastVisited) break;
            // Replace parent's child with the corresponding child of the removed node
            *(int*)(parentChildren + slot * 4) = *(int*)(lastVisited[2] + slot * 4);
            slot++;
        } while (slot <= (unsigned int)*(int*)((char*)this + 4));

        // Free the removed node's child array and the node itself
        FUN_009c8f10(lastVisited[2]); // free child array
        FUN_009c8eb0(lastVisited);    // free node

        // Decrement element count
        (*(int*)((char*)this + 0x10))--; // unaff_EDI[4] = count
    }
}