// FUNC_NAME: EventQueue::addEvent

// Reconstructed from Ghidra decompilation at 0x004d0740
// This function inserts a new event into a priority-sorted doubly linked list.
// The event contains a string message, a float priority, and a boolean flag.
// It returns a unique ID for the event.

struct EventNode {
    EventNode* next;          // +0x00
    EventNode* prev;          // +0x04
    char message[0xA0];       // +0x08
    uint32_t flags;           // +0xA8
    uint32_t id;              // +0xAC
    int32_t order;            // +0xB0 (used for insertion ordering, set to 0)
    float priority;           // +0xB4
};

class EventQueue {
public:
    EventNode* freeListHead;   // +0x5C
    EventNode* freeListTail;   // +0x60 (only used when free list becomes empty)
    EventNode* activeListHead; // +0x4C
    EventNode* activeListTail; // +0x50
    uint32_t someFlag;         // +0x48 (if 0, triggers a callback)
    CRITICAL_SECTION cs;       // +0x68
    uint32_t nextId;           // +0x0C

    int addEvent(const char* message, float priority, bool flag);
};

// External helper functions (not reconstructed)
void FUN_004d0920(); // Possibly allocates or initializes something
void FUN_004d0870(); // Possibly signals or wakes up a consumer

int EventQueue::addEvent(const char* message, float priority, bool flag) {
    EnterCriticalSection(&cs);
    FUN_004d0920();

    EventNode* node = freeListHead;
    EventNode* newNode = nullptr;

    if (node != nullptr) {
        // Remove from free list (singly linked)
        freeListHead = node->next;
        if (freeListHead == nullptr) {
            freeListTail = nullptr;
        } else {
            node->next = nullptr; // Not strictly necessary but safe
        }
        newNode = node;
    } else {
        newNode = nullptr; // No free node available; caller should handle
    }

    // Assign a unique ID
    nextId++;
    newNode->id = nextId;

    // Copy the message (max 0xA0 bytes)
    strncpy(newNode->message, message, 0xA0);

    // Set priority
    newNode->priority = priority;

    // Set flag bit 2 if requested
    if (flag) {
        newNode->flags |= 4;
    }

    // Insert into active list sorted by priority (ascending)
    if (activeListHead == nullptr) {
        // List is empty
        newNode->next = nullptr;
        newNode->prev = nullptr;
        activeListHead = newNode;
        activeListTail = newNode;
    } else {
        // Traverse from tail backwards to find insertion point
        EventNode* current = activeListTail;
        while (current != nullptr && current->order < 1 && current->priority < priority) {
            current = current->prev;
        }

        if (current == nullptr) {
            // Insert at head (all existing nodes have lower priority)
            newNode->next = activeListHead;
            newNode->prev = nullptr;
            activeListHead->prev = newNode;
            activeListHead = newNode;
        } else {
            // Insert after 'current'
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            } else {
                activeListTail = newNode;
            }
            current->next = newNode;
        }
    }

    // Reset order field (used for insertion ordering)
    newNode->order = 0;

    // If someFlag is 0, call a callback (e.g., signal a waiting thread)
    if (someFlag == 0) {
        FUN_004d0870();
    }

    LeaveCriticalSection(&cs);
    return newNode->id;
}