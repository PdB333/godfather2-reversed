// FUNC_NAME: ObjectPool::insertNode
// Function at 0x006a8a90: Inserts a node into a doubly linked list after initialization.
// The node structure: [0] = next, [1] = prev, [2] = value (handle/ID)
// Returns 1 if insertion succeeded (node->next and node->value are non-zero), else 0.

undefined1 ObjectPool::insertNode(int *node, float paramFloat)
{
    undefined1 result;
    float squared;
    undefined1 buffer[16]; // unused buffer for some computation
    int tempList[2];       // temporary list head storage
    int nodeValue;

    result = 0;
    // Initialize pool or allocate memory? Uses global DAT_00d5ccf8
    poolInitialize(paramFloat, 0x20, DAT_00d5ccf8);
    // Compute something with node address, buffer, and paramFloat squared
    squared = paramFloat * paramFloat;
    computeSomething(&node, buffer, squared);

    // Insert node into linked list (head stored in tempList[0])
    if ((node != tempList) && (*node != tempList[0])) {
        if (*node != 0) {
            // Remove node from its current list (if any)
            nodeDestructor(node);
        }
        *node = tempList[0]; // node->next = old head
        if (tempList[0] != 0) {
            node[1] = *(int *)(tempList[0] + 4); // node->prev = old head->prev? Actually sets node->prev to old head's prev? Wait: *(int*)(tempList[0]+4) is old head's prev. Then sets old head->prev = node.
            *(int **)(tempList[0] + 4) = node;
        }
    }
    node[2] = nodeValue; // set node value (from local_17c, uninitialized? Actually local_17c is set by earlier call? Not shown. Possibly from poolInitialize or computeSomething)
    if ((*node != 0) && (nodeValue != 0)) {
        result = 1;
    }
    postInsertUpdate(); // finalization
    return result;
}