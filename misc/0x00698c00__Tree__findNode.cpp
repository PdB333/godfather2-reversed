// FUNC_NAME: Tree::findNode
// Address: 0x00698c00
// Role: Binary tree search function for node insertion point.
// Uses global comparator (0x004d4b20) with single argument (key or address of node field).
void __thiscall Tree::findNode(void *this, int *outNodePtr, int key) {
    // +0x04: sentinel node pointer
    int *sentinel = reinterpret_cast<int *>(static_cast<char *>(this) + 4);
    // +0x0c: root node pointer
    int *currentNode = *reinterpret_cast<int **>(static_cast<char *>(this) + 12);
    int *lastCandidate = sentinel;

    // Traverse the binary tree. The node structure is assumed to have:
    // +0x00: left child pointer
    // +0x04: right child pointer
    // +0x08: key (int) — not directly accessed here
    while (currentNode != nullptr) {
        // Global comparator; only the search key is passed (likely missing node key argument)
        int cmp = FUN_004d4b20(key); // Compare key
        if (cmp < 0) {
            // Go left
            currentNode = reinterpret_cast<int *>(*currentNode);
        } else {
            // Go right and remember this node as the last candidate
            lastCandidate = currentNode;
            currentNode = reinterpret_cast<int *>(currentNode[1]);
        }
    }

    // Check if the last candidate is valid and its second field compares >=0
    if (lastCandidate != sentinel) {
        // Compare key with the address of the second field (right child?) of the candidate
        int cmp = FUN_004d4b20(reinterpret_cast<int>(lastCandidate + 4));
        if (cmp >= 0) {
            *outNodePtr = reinterpret_cast<int>(lastCandidate);
            return;
        }
    }

    // Default: return sentinel
    *outNodePtr = reinterpret_cast<int>(sentinel);
}