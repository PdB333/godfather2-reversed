// FUNC_NAME: compareNodeKey
struct CompareNode {
    int level;        // +0x00
    int padding;      // +0x04
    int type;         // +0x08 (1 = sentinel)
    unsigned int* key; // +0x0C
};

/**
 * Compares an external key (nodeKey) with the key stored in the given node.
 * Returns: -1 if node's key < external key, 0 if equal, 1 otherwise.
 * Special case: if node->type == 1 (sentinel), always returns -1.
 */
int __fastcall compareNodeKey(const CompareNode* node, unsigned int nodeKey) {
    // Sentinel node always considered less than any key
    if (node->type == 1) {
        return -1;
    }
    // Level < 2: apply standard comparison; otherwise return greater
    if (node->level < 2 && *node->key <= nodeKey) {
        return -(*node->key < nodeKey); // -1 if less, 0 if equal
    }
    return 1;
}