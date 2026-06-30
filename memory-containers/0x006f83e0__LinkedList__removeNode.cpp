// FUNC_NAME: LinkedList::removeNode
// Function at 0x006f83e0: Removes a node from a doubly linked list and deallocates its sub-objects and the node itself.
// The list layout (this):
//   +0x00: head (pointer to first node)
//   +0x04: tail (pointer to last node)
//   +0x08: count (number of nodes)
//   +0x10: allocator (pointer to object with vtable; vtable[1] destroys the node)
// Node layout:
//   +0x00: data (not accessed here)
//   +0x04: pointer to sub-object 1 (freed via FUN_004daf90)
//   +0x0C: pointer to sub-object 2 (freed via FUN_004daf90)
//   +0x14: next pointer
//   +0x18: prev pointer
// Input: nodePtr points to the pointer of the node to remove; after removal, *nodePtr is updated to the next node (or nullptr if removed last).
// Note: param_2 is unused. The output through EBX is identical to *nodePtr after update (handled by caller).

class LinkedList {
public:
    int* head;       // +0x00
    int* tail;       // +0x04
    int count;       // +0x08
    void* allocator; // +0x10 (vtable-pointer)

    // Removes the node pointed to by *nodePtr from the list, frees its sub-objects, and then destroys the node via the allocator.
    void removeNode(int** nodePtr) {
        int* node = *nodePtr;
        int* next = nullptr;
        if (node != nullptr) {
            next = *(int**)(node + 0x14); // node->next
        }

        *nodePtr = next; // Update outer pointer to next node

        if (node == head) {
            if (node == tail) {
                // Only node, list becomes empty
                tail = nullptr;
                head = nullptr;
            } else {
                // Remove head
                head = next;
                if (next != nullptr) {
                    *(int**)(next + 0x18) = nullptr; // next->prev = nullptr
                }
            }
        } else {
            int* prev = *(int**)(node + 0x18); // node->prev
            if (node == tail) {
                // Remove tail
                tail = prev;
                if (prev != nullptr) {
                    *(int**)(prev + 0x14) = nullptr; // prev->next = nullptr
                }
            } else {
                // Remove from middle
                *(int**)(prev + 0x14) = next; // prev->next = node->next
                if (next != nullptr) {
                    *(int**)(next + 0x18) = prev; // next->prev = node->prev
                }
            }
        }

        // Deallocate sub-objects
        if (*(void**)(node + 0x0C) != nullptr) {
            FUN_004daf90(node + 0x0C);
        }
        if (*(void**)(node + 4) != nullptr) {
            FUN_004daf90(node + 4);
        }

        // Destroy the node itself using allocator vtable method at offset 4
        (*(void (**)(int*, int))(**(int**)allocator + 4))(node, 0);

        count--;
    }
};

// Note: FUN_004daf90 is an internal deallocation function (likely operator delete or similar).