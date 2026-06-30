// FUNC_NAME: Entity::transferChildReferencesToManager
// Function address: 0x00583730
// Purpose: Transfers a set of child node pointers from this entity to a manager, handling reference counting and linked list removal/addition.
// The manager to use depends on whether the new parent ID (param_2) is found in a lookup table within parentInfo (param_3).

// Structures used
struct RefCountedNode {
    RefCountedNode* prev;      // +0x00
    RefCountedNode* next;      // +0x04
    char flag;                 // +0x08 (checked for zero before deletion)
    char refCount;             // +0x09
};

struct ListSentinel {
    RefCountedNode* head;      // +0x00 (inferred)
    RefCountedNode* tail;      // +0x04
    int someCount;             // +0x08
    int tail2;                 // +0x0c (probably end sentinel)
};

struct ParentLookupTable {
    int count;                 // +0x4c
    int* entries;              // +0x50 (array of 3-int entries, first int is ID)
};

struct ParentInfo {
    char unknown[0x70];
    ParentLookupTable* lookupTable; // +0x70
};

// Global sentinel variables
// These are assumed to be sentinel nodes for different lists
extern ListSentinel DAT_0120555c;  // for size pool 5?
extern ListSentinel DAT_01205560;  // for size pool 6?
extern ListSentinel DAT_01205564;  // for size pool 7?
extern ListSentinel DAT_01205588;  // for size pool 8?
extern ListSentinel DAT_0120558c;  // for size pool 9?

void Entity::transferChildReferencesToManager(int newParentId, ParentInfo* parentInfo) {
    RefCountedNode* thisPtr = this;  // in_EAX
    if (thisPtr == 0) return;

    ParentLookupTable* table = parentInfo->lookupTable;
    int* entries = table->entries;
    int entryCount = table->count;

    // Search through lookup table for newParentId
    for (int i = 0; i < entryCount; i++) {
        if (*entries == newParentId) {
            // Found: use manager from FUN_005861c0 (let's call it getManagerB)
            RefCountedNode* oldChild1 = thisPtr->children[0x3c]; // +0x3c
            RefCountedNode* oldChild2 = thisPtr->children[0x40]; // +0x40
            RefCountedNode* oldChild3 = thisPtr->children[0x44]; // +0x44

            thisPtr->children[0x3c] = 0;
            thisPtr->children[0x40] = 0;
            thisPtr->children[0x44] = 0;

            void* managerB = FUN_005861c0();  // returns some manager object

            // Restore old children
            thisPtr->children[0x3c] = oldChild1;
            thisPtr->children[0x40] = oldChild2;
            thisPtr->children[0x44] = oldChild3;

            // Transfer child at +0x3c
            if (oldChild1 != 0) {
                oldChild1->refCount++;
            }
            RefCountedNode* currentChild = *(RefCountedNode**)((int)managerB + 0x3c);
            if (currentChild != 0) {
                currentChild->refCount--;
                if (currentChild->flag == 0 && currentChild->refCount == 0) {
                    // Remove from list headed by DAT_01205588
                    removeFromList(currentChild, &DAT_01205588);
                }
            }
            *(RefCountedNode**)((int)managerB + 0x3c) = oldChild1;

            // Transfer child at +0x40
            if (oldChild2 != 0) {
                oldChild2->refCount++;
            }
            currentChild = *(RefCountedNode**)((int)managerB + 0x40);
            if (currentChild != 0) {
                currentChild->refCount--;
                if (currentChild->flag == 0 && currentChild->refCount == 0) {
                    removeFromList(currentChild, &DAT_0120558c);
                }
            }
            *(RefCountedNode**)((int)managerB + 0x40) = oldChild2;

            // Transfer child at +0x44
            if (oldChild3 != 0) {
                oldChild3->refCount++;
            }
            currentChild = *(RefCountedNode**)((int)managerB + 0x44);
            if (currentChild != 0) {
                currentChild->refCount--;
                if (currentChild->flag == 0 && currentChild->refCount == 0) {
                    removeFromList(currentChild, &DAT_0120555c);
                }
            }
            *(RefCountedNode**)((int)managerB + 0x44) = oldChild3;

            return;
        }
        entries += 3; // each entry is 12 bytes
    }

    // New parent ID not found in lookup table: use different manager (FUN_0056fdd0)
    void* managerA = FUN_0056fdd0();

    // Transfer children from offsets 0x34, 0x38, 0x3c, 0x40
    for (int offset = 0x34; offset <= 0x40; offset += 4) {
        RefCountedNode* oldChild = *(RefCountedNode**)((int)thisPtr + offset);
        if (oldChild != 0) {
            oldChild->refCount++;
        }
        RefCountedNode* currentChild = *(RefCountedNode**)((int)managerA + offset);
        if (currentChild != 0) {
            currentChild->refCount--;
            if (currentChild->flag == 0 && currentChild->refCount == 0) {
                // Remove from appropriate list based on offset
                ListSentinel* sentinel;
                switch (offset) {
                    case 0x34: sentinel = &DAT_01205564; break;
                    case 0x38: sentinel = &DAT_01205560; break;
                    case 0x3c: sentinel = &DAT_01205588; break;
                    case 0x40: sentinel = &DAT_0120558c; break;
                    default: sentinel = 0; break;
                }
                if (sentinel != 0) {
                    removeFromList(currentChild, sentinel);
                }
            }
        }
        *(RefCountedNode**)((int)managerA + offset) = oldChild;
    }
}

// Helper function to remove a node from a doubly linked list with sentinel
inline void removeFromList(RefCountedNode* node, ListSentinel* sentinel) {
    RefCountedNode* prev = node->prev;
    RefCountedNode* next = node->next;
    if (prev != 0) {
        prev->next = next;
    }
    if (next != 0) {
        next->prev = prev;
    } else {
        // Update sentinel tail
        sentinel->tail = sentinel->head; // actually sentinel+8 = sentinel+4
        sentinel->head = prev; // sentinel+4 = prev
        if (prev == 0) {
            sentinel->head = sentinel->tail2; // sentinel+8 = sentinel+0xc
        }
    }
}