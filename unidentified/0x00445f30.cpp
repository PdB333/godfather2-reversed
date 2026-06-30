// FUN_00445f30: QuadKeyTree::searchNode
void __fastcall QuadKeyTree::searchNode(int* node, int* quadKey)
{
    // node points to a node in a tree or linked list.
    // Offsets (as int offsets from node pointer):
    // +0x10 : pointer to next/child node
    // +0x20, +0x24, +0x28, +0x2c : four ints forming a quad key
    int* parent = nullptr;   // iVar2 - previous node (used for traversal)
    int* nextChild;          // iVar3 - next node after comparison

    do {
        if (node == nullptr) {
            return; // End of search path, no match found
        }

        // Compare the 4-int key of the current node with the search key
        if (node[0x20/4] != quadKey[0] || node[0x24/4] != quadKey[1] ||
            node[0x28/4] != quadKey[2] || node[0x2c/4] != quadKey[3])
        {
            // Key mismatch - move to the child/next pointer stored at +0x10
            int* nextPtr = (int*)((char*)node + 0x10); // pointer to next node
            node = parent;         // Go back to parent (previously visited node)
            nextChild = *nextPtr;  // The actual next node from the mismatch path
        }
        else {
            // Key matches - flag the current node as the result (nextChild = node)
            // The comma operator in the condition sets nextChild = node before the final comparison,
            // but since the condition is false (all equal), the if-block is skipped.
            nextChild = node;
        }

        // Update parent and node for next iteration
        bool nodeWasNull = (node == nullptr);
        parent = node;
        node = nextChild;

    } while (nodeWasNull); 
    // Continue if the previous node was null – this effectively
    // traverses a chain: when a null node is encountered, it jumps
    // to the child stored before the null (linked list traversal).
}