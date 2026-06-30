// FUNC_NAME: SkipList::findNode

// Skip list node: offset 0 = key (int), offset 4 = pad/unused, offset 8 = forward[] array of int* pointers (level-based)
struct SkipListNode {
    int key;        // +0x00
    int pad;        // +0x04 (unused, probably alignment)
    int* forward[]; // +0x08
};

// Skip list header: pointer to head node and current maximum level
struct SkipList {
    SkipListNode* head; // +0x00
    int maxLevel;       // +0x04
};

// 0x0065dda0
SkipListNode* __thiscall SkipList::findNode(int* keyPtr) {
    SkipListNode* current = this->head;          // piVar4 = *param_1
    int level = this->maxLevel;                  // iVar3 = param_1[1]

    while (level >= 0) {
        // Get next node at current level
        SkipListNode* next = (SkipListNode*)current->forward[level]; // piVar1 = *(int**)(piVar4[2] + level*4)

        if (next != nullptr) {
            // Advance while next node's key is less than the search key
            do {
                SkipListNode* prev = current;                 // piVar2 = piVar1
                if (*keyPtr <= prev->key) break;             // if (*param_2 <= *piVar2) break
                current = next;                               // piVar4 = piVar2
                next = (SkipListNode*)current->forward[level]; // piVar1 = *(int**)(piVar2[2] + iVar3*4)
                if (next == nullptr) break;
            } while (next != nullptr);
        }

        // After advancing, check the node at level 0
        SkipListNode* candidate = (SkipListNode*)current->forward[0]; // piVar1 = *(int**)piVar4[2]
        if (candidate == nullptr) break;

        if (candidate->key == *keyPtr) {
            return candidate;
        }

        level--;
    }

    return nullptr;
}