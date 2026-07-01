// FUNC_NAME: SkipList::findNode
// Function address: 0x008ab770
// This function searches for a node with a given key in a skip list structure.
// The structure has a root node and an array of forward pointers per level.
// It traverses from the highest level down, moving horizontally until finding a node with key >= searchKey,
// then checks the level-0 successor. If a match is found, it returns the node; otherwise returns null.

struct SkipListNode {
    uint key;                   // +0x00
    uint padding[1];            // +0x04 (unused in this function?)
    SkipListNode** forward;     // +0x08 pointer to array of forward pointers (one per level)
};

struct SkipList {
    SkipListNode* head;         // +0x00
    int32_t levelCount;         // +0x04 number of levels (highest index)
};

void __thiscall SkipList::findNode(
    const uint* searchKey,      // param_3 - pointer to key to find
    void** outNode              // param_2 - output pointer to found node
) {
    SkipListNode* currentNode = this->head;         // puVar4
    int32_t level = this->levelCount;               // iVar3

    for (; level >= 0; --level) {
        // Get the forward pointer at the current level from the current node
        SkipListNode* nextNode = currentNode->forward[level]; // puVar1

        if (nextNode != nullptr) {
            do {
                SkipListNode* candidate = nextNode; // puVar2
                // If the search key is less than or equal to candidate's key, stop moving forward
                if (*searchKey <= candidate->key) {
                    break;
                }
                // Otherwise, advance to the next node at this level
                nextNode = candidate->forward[level];
                currentNode = candidate; // puVar4 updated to last node with key < searchKey
            } while (nextNode != nullptr);
        }

        // After the horizontal traversal at this level, check the level-0 successor of current node
        SkipListNode* targetNode = currentNode->forward[0]; // puVar1
        if (targetNode == nullptr) {
            break; // No more nodes
        }
        if (targetNode->key == *searchKey) {
            *outNode = targetNode; // Found match
            return;
        }
    }

    *outNode = nullptr; // Not found
    return;
}