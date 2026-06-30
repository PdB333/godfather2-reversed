// FUNC_NAME: BSTree::findOrInsert
void __thiscall BSTree::findOrInsert(int thisPtr, int *result, int key) {
    // Node structure (size >= 0x30):
    // +0x00: left child (pointer)
    // +0x08: right child (pointer)
    // +0x0C: key (usually 4 bytes)
    // +0x29: byte flag (0 = occupied/sentinel, !=0 = free/empty)
    // Header structure at thisPtr+0x4:
    // +0x00: left child pointer
    // +0x04: right child pointer

    int *headerPtr = *(int **)(thisPtr + 4); // pointer to header node
    int *currentNode = (int *)headerPtr[1];  // start traversal from header's right child
    bool lastDirectionLeft = true;            // direction from the parent to the current node (true = left, false = right)

    // Traverse the tree until we find an empty/free node (flag at +0x29 != 0)
    char flag;
    flag = *(char *)(currentNode + 0x29 / 4); // byte at offset 0x29 (adjust for pointer casting)
    int *parentNode = headerPtr;
    while (flag == '\0') {
        int cmp = keyCompare((int *)((int)currentNode + 0xC), key); // compare key of node with given key
        lastDirectionLeft = (cmp < 0);
        int *nextNode;
        if (lastDirectionLeft) {
            nextNode = (int *)*currentNode;               // left child
        } else {
            nextNode = (int *)currentNode[2];             // right child (offset 8)
        }
        parentNode = currentNode;
        currentNode = nextNode;
        flag = *(char *)(currentNode + 0x29 / 4);
    }

    int *thisStorage = thisPtr;     // save this pointer for later
    int *foundParent = parentNode;  // the parent of the free node

    if (lastDirectionLeft) {
        // We came from left. Check if the parent is the header's left child (i.e., the tree is empty on left side?)
        // If so, directly insert a new node at header's left.
        if (parentNode == (int *)*(int *)headerPtr) {
            int *newNodeResult = (int *)insertNode(&thisStorage, 1, parentNode, key);
            int newKey = *newNodeResult;
            result[1] = newNodeResult[1];
            *(char *)(result + 2) = 1;   // flag: inserted
            *result = newKey;
            return;
        }
        handleError(); // maybe invalid state, abort
    }

    currentNode = foundParent;
    int cmp = keyCompare(key); // ??? likely comparing key with something (maybe with the sentinel's key)
    if (cmp >= 0) {
        // Key already exists or found sentinel? Return without insertion.
        result[1] = (int)foundParent;
        *(char *)(result + 2) = 0;   // flag: not inserted
        *result = thisStorage;
        return;
    }

    // Insert a new node
    int *newNodeResult = (int *)insertNode(&thisStorage, lastDirectionLeft, foundParent, key);
    int newKey = *newNodeResult;
    result[1] = newNodeResult[1];
    *(char *)(result + 2) = 1;   // flag: inserted
    *result = newKey;
    return;
}