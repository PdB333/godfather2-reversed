// FUNC_NAME: DoublyLinkedList::addToFront
// 0x0093e4c0 - Intrusive doubly-linked list prepend operation.
// Inserts a node at the head of a linked list and updates dirty flag.

struct ListNode {
    ListNode* next; // +0x00
    ListNode* prev; // +0x04
};

// Global memory tracker pointer (used for dirty range tracking)
extern void* g_memoryTracker; // DAT_012069c4

// Function to mark a memory range as dirty (declared elsewhere)
void memoryTrackerMarkDirty(void* list, void* tracker, uint32_t size); // FUN_00408900

class DoublyLinkedList {
    // Offsets relative to 'this' (param_1)
    // +0x48: head
    // +0x4c: tail
    // +0x50: count
    // +0x5c: flags (bit0 = dirty)

public:
    ListNode* head;   // +0x48
    ListNode* tail;   // +0x4c
    int count;        // +0x50
    uint16_t flags;   // +0x5c

    // Prepend a node to the list
    void addToFront(ListNode* node) {
        count++;                          // +0x50
        node->next = head;                // node[0] = head
        node->prev = nullptr;             // node[1] = 0

        if (head == nullptr) {
            tail = node;                  // +0x4c
        } else {
            head->prev = node;            // head[1] = node (prev)
        }

        head = node;                      // +0x48

        // If dirty flag is not set, mark list as dirty
        if ((flags & 1) == 0) {
            if (g_memoryTracker != nullptr) {
                memoryTrackerMarkDirty(this, g_memoryTracker, 0x8000);
            }
            flags |= 1;                   // set dirty bit
        }
    }
};