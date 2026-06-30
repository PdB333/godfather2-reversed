// FUNC_NAME: SkipList::find
// Function at 0x004988f0 - Skip list search by key
// Structure offsets:
//   SkipList: +0x00 head (SkipListNode*), +0x04 maxLevel (int)
//   SkipListNode: +0x00 key (uint), +0x04 forward (uint** - array of next pointers per level)

void* __thiscall SkipList::find(uint* keyPtr) {
    uint targetKey = *keyPtr;                          // Key to search for
    SkipListNode* curNode = head;                      // Start from header node
    int level = maxLevel;                              // Begin at the highest level

    while (level >= 0) {
        // Follow forward pointers at this level while key is greater than next node's key
        SkipListNode* fwd = curNode->forward[level];   // Next node at current level
        if (fwd != nullptr) {
            do {
                SkipListNode* candidate = fwd;
                if (targetKey <= candidate->key) {     // Stop if key <= candidate's key
                    break;
                }
                fwd = candidate->forward[level];       // Move to next node at same level
                curNode = candidate;                   // Advance current node
            } while (fwd != nullptr);
        }

        // After horizontal pass, check the immediate next node at level 0
        SkipListNode* check = curNode->forward[0];     // Level 0 forward pointer
        if (check == nullptr) {                        // No more nodes
            break;
        }
        if (check->key == targetKey) {                 // Key match found
            return check;
        }
        level--;                                       // Descend to next lower level
    }
    return nullptr;                                    // Not found
}