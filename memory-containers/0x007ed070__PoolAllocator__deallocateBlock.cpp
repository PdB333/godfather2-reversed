// FUNC_NAME: PoolAllocator::deallocateBlock
// Address: 0x007ed070
// Role: Removes a node from a free list, optionally matching by typeId, key, or a predicate callback,
// then frees the node and merges with adjacent free block.

class PoolAllocator {
public:
    // Node structure for free list (doubly-linked with sentinel head)
    struct Node {
        Node* pNext;       // +0x00
        Node* pPrev;       // +0x04
        void* vtable;      // +0x08 (set to a marker vtable after freeing)
        int size;          // +0x0c
        void* data;        // +0x10 (optional associated data)
        int key;           // +0x14 (optional key for matching)
        short refCount;    // +0x1a (reference count, must be zero before freeing)
        byte flags;        // +0x20 (bit0 = 0 means data can be released)
        int typeId;        // +0x1c (type identifier for matching)
    };

    // The free list head structure (embedded at this+0x18)
    struct FreeListHead {
        Node** ppSentinel; // +0x00? Actually *ppSentinel points to the first node
        int count;         // +0x1c (number of free nodes)
    };

private:
    FreeListHead* freeListHead; // at this+0x18

    // Assert/error handler (inlined in original)
    void assertFailure() {
        // __asm int 3
    }

    // Spin-wait until reference count drops to zero
    void waitForRefCountZero(Node* node) {
        while (node->refCount != 0) {
            // Yield (simulated)
            FUN_00408090(); // likely a yield/context switch
        }
    }

    // Release associated data if needed
    void releaseData(Node* node) {
        if (node->data != nullptr && ((node->flags & 1) == 0)) {
            // Call release function on data (assumes vtable at data object)
            (**(void (__thiscall**)(int))node->data)(1);
        }
    }

    // Deallocate the node memory via the head's vtable
    void deallocateNodeMemory(Node* node) {
        // Call member function at vtable[1] (size 0x24 = 36 bytes)
        (**(void (__thiscall**)(void*, int))freeListHead)(node, sizeof(Node));
    }

public:
    // Remove and free a node from the list matching given criteria.
    // typeId: must match node->typeId (if nonzero)
    // keyPtr: if not null, must match node->key
    // predicate: if not null, must return true for (totalSize, node->key, node->typeId, node->data)
    // Returns number of nodes removed (usually 1)
    int deallocateBlock(int typeId, int* keyPtr, int* predicate) {
        Node* head = *freeListHead->ppSentinel; // sentinel node (act as terminator)
        Node* current = head; // start from sentinel? Actually code sets piVar7 = **(int**)(iVar2 + 0x18) => head
        int totalSize = 0; // local_18
        int removedCount = 0; // local_14

        do {
            // Validate list consistency
            if (freeListHead == nullptr || freeListHead != *(FreeListHead**)(this + 0x18)) {
                assertFailure();
            }
            if (current == head) { // reached sentinel? Actually if current == head (sentinel), return
                return removedCount;
            }
            if (freeListHead == nullptr) {
                assertFailure();
            }
            if (current == *(Node**)(freeListHead + 0x18)) { // sentinel check
                assertFailure();
            }

            int nodeSize = current->size;
            totalSize += nodeSize;

            // Check if this node matches criteria
            if (typeId != 0) {
                if (current == *(Node**)(freeListHead + 0x18)) {
                    assertFailure();
                }
                if (current->typeId != typeId) {
                    // No match - skip
                    goto advance;
                }
            }

            if (keyPtr != nullptr) {
                if (current == *(Node**)(freeListHead + 0x18)) {
                    assertFailure();
                }
                if (*keyPtr != current->key) {
                    goto advance;
                }
            }

            if (predicate != nullptr) {
                if (current == *(Node**)(freeListHead + 0x18) && ...) { // redundant assert
                    assertFailure();
                }
                // Call predicate function: (void*)(*predicate) with params (totalSize, &current->key, current->typeId, current->data)
                bool predicateResult = (**(bool (__thiscall**)(int, int*, int, void*))(*predicate + 4))(totalSize, &current->key, current->typeId, current->data);
                if (!predicateResult) {
                    goto advance;
                }
            }

            // Found matching node - remove it
            Node* next = current->pNext;

            // Unlink from list
            if (current != *(Node**)(freeListHead + 0x18)) { // not the sentinel
                current->pPrev->pNext = next;
                next->pPrev = current->pPrev;
            }

            // Mark node as freed (set vtable to a global marker)
            current->vtable = &PTR_FUN_00d6ffac; // marker for freed block

            // Wait for reference count to drop
            waitForRefCountZero(current);

            // Release associated data if needed
            releaseData(current);

            // Actually free the node memory via the allocator
            deallocateNodeMemory(current);

            // Decrement free count
            freeListHead->count--;

            // Coalesce with next free block if not sentinel
            // Get current first node after removal
            Node* newFirst = *freeListHead->ppSentinel;
            if (freeListHead != *(FreeListHead**)(this + 0x18)) {
                assertFailure();
            }
            if (next != newFirst) {
                // Coalesce: add removed node's size to next node
                if (next == *(Node**)(freeListHead + 0x18)) {
                    assertFailure();
                }
                next->size += nodeSize;
            }

            removedCount++;
            // Restart from beginning? The code sets current = next and continues
            current = next;
        } while (true);

advance:
        if (current == *(Node**)(freeListHead + 0x18)) {
            assertFailure();
        }
        current = current->pNext;
        goto loop_continue;
    }
};