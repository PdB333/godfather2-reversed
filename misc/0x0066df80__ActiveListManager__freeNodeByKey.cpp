// FUNC_NAME: ActiveListManager::freeNodeByKey
// Function address: 0x0066df80
// Role: Removes all nodes with a given key from the active list and returns them
//       to the free pool. Updates manager totals and counts accordingly.
struct Node {
    Node* next;       // +0x00
    int key;          // +0x04
    int unknown;      // +0x08 (unused after removal)
    int value;        // +0x0C
};

struct FreeNodePool {
    int totalAllocated; // +0x04
    short usedCount;    // +0x08 (actually a short followed by padding)
    Node* freeList;     // +0x14
};

class ActiveListManager {
public:
    Node* activeListHead; // +0x14
    int totalActive;      // +0x0C
    int activeCount;      // +0x10

    void freeNodeByKey(FreeNodePool* pool, int key) {
        Node** prevPtr = &activeListHead;
        Node* current = activeListHead;

        while (current) {
            Node* next = current->next;
            if (current->key == key) {
                // Remove from active list
                totalActive -= current->value;
                activeCount--;
                *prevPtr = next;

                // Return node to free pool
                current->next = pool->freeList;
                current->key = 0;
                current->value = 0;
                pool->usedCount--;
                pool->totalAllocated -= (current->value + 0); // subtract original value before zeroed (already captured above)
                pool->freeList = current;

                // prevPtr stays the same (pointing to same address, now containing 'next')
                current = next;
            } else {
                prevPtr = &current->next;
                current = next;
            }
        }
    }
};