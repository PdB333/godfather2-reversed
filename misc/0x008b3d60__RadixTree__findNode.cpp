// FUNC_NAME: RadixTree::findNode
void __thiscall RadixTree::findNode(uint *this, uint **outNode, uint *key)
{
    uint *currentNode;
    uint *childNode;
    int level;
    uint *nextNode;

    currentNode = (uint *)*this; // this[0] = root node pointer
    level = this[1]; // this[1] = number of levels (depth)

    // Traverse from highest level down to 0
    for (; level >= 0; level--) {
        // Get child at current level index from current node
        childNode = *(uint **)(currentNode[5] + level * 4);
        if (childNode != (uint *)0x0) {
            // Follow the chain of nodes at this level until key <= current node's key
            do {
                nextNode = childNode;
                if (*key <= *nextNode) break;
                childNode = *(uint **)(nextNode[5] + level * 4);
                currentNode = nextNode;
            } while (childNode != (uint *)0x0);
        }

        // Check the first child (index 0) of the last node in the chain
        childNode = *(uint **)currentNode[5]; // child at index 0
        if (childNode == (uint *)0x0) break;
        if (*childNode == *key) {
            *outNode = childNode;
            return;
        }
    }

    *outNode = (uint *)0x0;
    return;
}