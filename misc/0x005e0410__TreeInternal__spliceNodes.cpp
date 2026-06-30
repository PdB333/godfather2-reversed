// FUNC_NAME: TreeInternal::spliceNodes
// Function address: 0x005e0410
// Role: Internal helper for inserting/splicing nodes in a balanced tree (likely red-black tree).
// Uses debug assertions (FUN_00b97aea) to validate node pointers.
// The tree is stored as a self-referential circular structure (sentinel node) at this+0x1c.
// this+0x20 is a flag or size.

void TreeInternal::spliceNodes(int* outPair, int nodeA, int nodeB, int nodeC, int nodeD)
{
    int rootVal; // dereferenced from this->sentinel (offset 0x1c)
    int localBuffer[8]; // unused buffer for temporary storage

    // Read the root's first child pointer (likely leftmost or rightmost)
    rootVal = **(int**)(this + 0x1c);

    // Assert: nodeA must be null or equal to this (special case for sentinel)
    if ((nodeA == 0) || (nodeA != this)) {
        debugAssert(); // FUN_00b97aea - crash if assertion fails
    }

    // If nodeB equals the saved root value, handle the special case where nodeB points to root
    if (nodeB == rootVal) {
        // Re-read the root pointer from this+0x1c (maybe changed?)
        rootVal = *(int*)(this + 0x1c);

        // Assert: nodeC must be null or equal to this
        if ((nodeC == 0) || (nodeC != this)) {
            debugAssert();
        }

        // If nodeD also equals root, execute a special initialisation/link setup
        if (nodeD == rootVal) {
            // Detach the child at offset 4 from the root node (possibly right child or prev)
            detachNode(*(int*)(*(int*)(this + 0x1c) + 4)); // FUN_005e1400

            // Make the root's own child point to itself (circular self-link)
            *(int*)(*(int*)(this + 0x1c) + 4) = *(int*)(this + 0x1c);

            // Clear flag at offset 0x20
            *(int*)(this + 0x20) = 0;

            // Set root's left/prev pointer to itself (offset 0)
            **(int**)(this + 0x1c) = *(int*)(this + 0x1c);

            // Set root's right/next field (offset 8) to itself
            *(int*)(*(int*)(this + 0x1c) + 8) = *(int*)(this + 0x1c);

            // Output: pair[0] = original root value (before self-link?), pair[1] = this
            outPair[1] = **(int**)(this + 0x1c); // note: after self-link, this is root's self address
            *outPair = this;
            return;
        }
    }

    // Generic search/splice loop - walk the tree until nodeB equals nodeD
    while (true) {
        // Assert: nodeA must be null or equal to nodeC
        if ((nodeA == 0) || (nodeA != nodeC)) {
            debugAssert();
        }
        if (nodeB == nodeD) break;

        // Perform an iteration step (likely move to next node in traversal)
        advanceSearch();                  // FUN_005e15c0 - maybe move to child/parent
        compareAndUpdate(this, localBuffer, nodeA, nodeB); // FUN_005e0c80
    }

    // After loop, store the matching pair into output
    outPair[1] = nodeB;
    *outPair = nodeA;
    return;
}