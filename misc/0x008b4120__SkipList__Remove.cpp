// FUNC_NAME: SkipList::Remove

#include <cstdint>

// Node in a skip list. Forward array size is maxLevel+1.
struct SkipListNode {
    uint32_t key;                 // +0x00
    // The +0x14 field is a pointer to an array of forward pointers (one per level)
    SkipListNode** forward;       // +0x14
};

// External memory operations (EA allocator wrappers)
extern void FreeForwardArray(SkipListNode** arr);   // (FUN_009c8f10)
extern void FreeNode(SkipListNode* node);           // (FUN_009c8eb0)

// SkipList member function: erase node with given key.
// On entry, param_1 = this, param_2 = pointer to key to remove.
void __thiscall SkipList::Remove(uint32_t* keyPtr) {
    SkipList* self = this;
    int32_t level = self->maxLevel;  // start from highest level
    SkipListNode* current = self->head;

    if (level < 0) {
        return; // empty list
    }

    // Search: for each level from highest to lowest, move forward until
    // the next key is >= target. Store the predecessor (the node just before
    // the target or the last node at that level) in the update array.
    // The update array is assumed to be large enough (size >= self->maxLevel+1).
    // We write update[level] after processing the level (level index corresponds to
    // the level of the forward pointer we will later modify).
    do {
        SkipListNode* next = current->forward[level];
        if (next != nullptr) {
            SkipListNode* follow = next;
            do {
                next = follow;
                if (*keyPtr <= follow->key) {
                    break;
                }
                follow = follow->forward[level];
                current = follow;
                // Note: current tracks the node we are at, not the predecessor.
                // Actually the loop structure: We start with follow = first child of current.
                // Then we iterate until we find a node where key <= target.
                // At that point, next points to that node, and current points to the node before it (predecessor).
                // But careful: In the decompiled code, puVar5 is updated to puVar6 (the current node) before moving to next.
                // So the final puVar5 is the predecessor.
            } while (follow != nullptr);
        }
        // After the inner loop, current holds the predecessor at this level.
        level--;
        self->update[level + 1] = current; // write to update[level+1]? Actually the expression writes to index (level+1) after decrement.
        // Let's confirm: In the original, iVar3 is decremented first, then write to param_1[5] + 4 + iVar3*4.
        // That means write to index (iVar3+1) using the new iVar3.
        // So the first iteration (iVar3 = maxLevel) writes to index maxLevel, then maxLevel-1, etc.
        // So we store predecessor at level (oldLevel) in update[oldLevel].
        // So we can write: self->update[level+1] = current; (since level was decremented, the old level is level+1)
    } while (level >= 0); // the while condition checks after decrement? Actually the original loops while (-1 < iVar3) and decrement at end, so condition check before decrement. We've used a do-while that checks after the body to mirror the decrement before write? Let's adjust: The original is a do-while that runs while iVar3 > -1. It decrements at the end of each iteration. So we'll use for(int level = self->maxLevel; level >= 0; level--) { ... update[level] = current; } That is simpler.
    // Actually rewrite with for loop for clarity.

    // Let's redo the search with a standard for loop matching the algorithm:
    // We'll use the original logic but express more cleanly.
}

// Better version:

void __thiscall SkipList::Remove(uint32_t* keyPtr) {
    SkipList* self = this;
    int32_t level;
    SkipListNode* current = self->head;
    SkipListNode* toDelete = nullptr;

    // For each level descending, find the predecessor.
    for (level = self->maxLevel; level >= 0; level--) {
        SkipListNode* next = current->forward[level];
        // Walk along the level's chain until the next key >= target.
        while (next != nullptr) {
            if (*keyPtr <= next->key) {
                break;
            }
            current = next;
            next = next->forward[level];
        }
        // Record predecessor at this level.
        self->update[level] = current;
    }

    // After the loop, toDelete is the node just after the predecessor at level 0.
    toDelete = self->update[0]->forward[0];
    if (toDelete != nullptr && toDelete->key == *keyPtr) {
        // Remove from all levels.
        for (level = 0; level <= self->maxLevel; level++) {
            // Check if the predecessor's forward at this level points to the node to delete.
            // (Should be true for levels where the node exists.)
            SkipListNode* pred = self->update[level];
            SkipListNode** forwardArray = reinterpret_cast<SkipListNode**>(pred->forward);
            if (forwardArray[level] != toDelete) {
                break; // node not at this level (or inconsistency)
            }
            // Bypass the deleted node.
            forwardArray[level] = toDelete->forward[level];
        }
        // Free the node's forward array and the node itself.
        FreeForwardArray(toDelete->forward);
        FreeNode(toDelete);
        self->count--;
    }
}