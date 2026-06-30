// FUN_004399a0: SkipList::findNode
struct SkipListNode {
    uint32_t key;       // +0x00
    // ... other fields
    uint32_t* forwardArray; // +0x14 pointer to array of forward pointers indexed by level
};

struct SkipList {
    SkipListNode* head; // +0x00 pointer to head node (sentinel with minimum key)
    int32_t maxLevel;   // +0x04 highest level index (levels 0..maxLevel)
};

void __thiscall SkipList::findNode(SkipList* this, uint32_t* keyPtr) {
    uint32_t searchKey = *keyPtr;
    SkipListNode* current = this->head;
    
    // Traverse from highest level down to level 0
    for (int32_t level = this->maxLevel; level >= 0; level--) {
        // Advance along this level while forward node exists and its key < searchKey
        SkipListNode* next = *(SkipListNode**)(current->forwardArray + level);
        if (next != nullptr) {
            do {
                SkipListNode* candidate = next;
                // Stop if candidate's key is >= searchKey
                if (searchKey <= candidate->key) {
                    break;
                }
                next = *(SkipListNode**)(candidate->forwardArray + level);
                current = candidate;
            } while (next != nullptr);
        }
        
        // Check the immediate successor at level 0 from current position
        SkipListNode* bottomNext = *(SkipListNode**)current->forwardArray;
        if (bottomNext == nullptr) {
            break;
        }
        if (bottomNext->key == searchKey) {
            // Found node; return it via implicit 'eax' (__thiscall return convention)
            return bottomNext; // Note: actual assembly sets *in_EAX, but code is void; we'll treat as returning pointer
        }
    }
    
    return nullptr; // Not found; *in_EAX = 0
}