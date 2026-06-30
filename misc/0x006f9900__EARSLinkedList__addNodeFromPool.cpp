// FUNC_NAME: EARSLinkedList::addNodeFromPool
// Function address: 0x006f9900
// Role: Allocates a new node from a memory pool (srcList) and appends it to the tail of a linked list (this).
// The srcList appears to be a pool of pre-allocated nodes, and the new node is linked into that pool before being appended.
// Node structure:
//   +0x10: next in pool list
//   +0x14: prev in pool list
//   +0x18: next in main list
//   +0x1c: prev in main list

void __fastcall EARSLinkedList::addNodeFromPool(int *thisList, int *srcList)
{
    int *newNode;
    int *poolNext;
    int *poolPrev;
    int *allocTag;

    // Determine allocation tag (custom memory pool identifier)
    allocTag = (int *)thisList[3];
    if (allocTag == (int *)0x0) {
        allocTag = (int *)0x01218a14; // Default tag
    }

    // Allocate a new node (size 0x20 = 32 bytes) using custom allocator
    // The allocator function pointer is stored at thisList[4]
    newNode = (int *)((code *)(*(int **)thisList[4])[0])(0x20, allocTag);
    if (newNode != (int *)0x0) {
        // Initialize the node's pool list links using srcList
        // This seems to insert the node into srcList's free list or pool
        // srcList+0x10 is probably the head of srcList's internal list
        FUN_004d3b50(srcList); // Probably a constructor or initializer (address 0x004d3b50)
        poolNext = (int *)*(int *)(srcList + 0x10); // Get first node in srcList's pool
        newNode[0x10 / 4] = (int)poolNext; // newNode->poolNext = poolNext
        newNode[0x14 / 4] = 0;              // newNode->poolPrev = NULL
        if (poolNext != (int *)0x0) {
            newNode[0x14 / 4] = *(int *)(poolNext + 4); // newNode->poolPrev = poolNext->poolPrev (??)
            *(int **)(poolNext + 4) = (int *)(newNode + 0x10); // poolNext->poolPrev = newNode->poolNext (??)
        }
    }

    // Append the new node to the tail of the main list (thisList)
    if (thisList[1] != 0) { // If tail exists
        // Write newNode to tail->next (at offset 0x18)
        *(int *)(thisList[1] + 0x18) = (int)newNode;
        // Write tail pointer to newNode->prev (at offset 0x1c)
        *(int *)(*(int *)(thisList[1] + 0x18) + 0x1c) = thisList[1];
        // Update tail
        thisList[2] = thisList[2] + 1; // Increment count
        thisList[1] = *(int *)(thisList[1] + 0x18); // tail = tail->next (which is newNode)
        return;
    }

    // List was empty
    thisList[2] = thisList[2] + 1; // Increment count
    thisList[1] = (int)newNode;    // Set tail to newNode
    thisList[0] = (int)newNode;    // Set head to newNode
}