// FUNC_NAME: SkipList::search

// Reconstructed C++ function for skip list search operation.
// Function at 0x00968e40.

struct SkipListNode {
    int key;                     // +0x00: node key
    int value;                   // +0x04: associated value (unused in search, but exists)
    int** forward;               // +0x08: pointer to array of forward pointers (one per level)
};

class SkipList {
public:
    SkipListNode* head;          // +0x00: sentinel head node
    int levelCount;              // +0x04: number of levels (max level + 1)
    // class is usually larger (e.g., random seed, etc.), but only these fields used here
};

void __thiscall SkipList::search(SkipList* this, SkipListNode** outResult, int key) {
    // outResult is int* in original, but we treat as pointer to pointer
    SkipListNode* current = this->head;  // +0x00
    int level = this->levelCount;        // +0x04, outer loop index (top level down to 0)

    for (; level >= 0; level--) {
        SkipListNode* next = current->forward[level];  // +0x08[level]
        if (next != nullptr) {
            do {
                SkipListNode* node = next;
                if (key <= node->key) break;           // stop when node's key >= key
                next = node->forward[level];           // advance to next node at same level
                current = node;
            } while (next != nullptr);
        }

        // Move to the base level (level 0) to check exact match
        SkipListNode* candidate = current->forward[0]; // first element of forward array
        if (candidate == nullptr) break;               // no further nodes
        if (candidate->key == key) {
            *outResult = candidate;
            return;
        }
    }

    *outResult = nullptr;                              // key not found
    return;
}