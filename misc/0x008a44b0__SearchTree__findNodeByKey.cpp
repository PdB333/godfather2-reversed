// FUNC_NAME: SearchTree::findNodeByKey
// Address: 0x008a44b0
// This function searches a multi-level tree structure for a node with a given key.
// The tree is organized as a series of levels (indexed by a decrementing counter),
// where each node has an array of child pointers at offset +0x8 (one per level).
// The outer loop traverses levels from highest to lowest. For each level, it follows
// the child chain at that level, stopping when the stored key <= search key.
// Then it checks the first child (level 0) of the last node for an exact match.
// Returns the found node pointer via param_2 (result), or nullptr if not found.

void __thiscall SearchTree::findNodeByKey(int **result, int *key) {
    Node *currentNode;   // piVar4
    Node *child;         // piVar1
    Node *tempNode;      // piVar2
    int level;           // iVar3

    currentNode = (Node *)this->root;          // this[0] = root node pointer
    // Iterate levels from highest down to 0
    for (level = this->depth; level >= 0; level--) {
        // Get child pointer at current level from current node's children array (offset +0x8)
        child = currentNode->children[level];
        if (child != nullptr) {
            do {
                tempNode = child;
                // Stop descending if search key <= current node's key
                if (*key <= tempNode->value) break;
                // Follow next node at same level
                child = tempNode->children[level];
                currentNode = tempNode;
            } while (child != nullptr);
        }
        // After descending at this level, examine the first child (level 0) of the final node
        child = currentNode->children[0];
        if (child == nullptr) break;
        if (child->value == *key) {
            *result = child;
            return;
        }
    }
    *result = nullptr;
}