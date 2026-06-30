// FUNC_NAME: EventScheduler::updateTimers

#include <cstdint>

// Timer node structure (size: 12 bytes, align 4)
struct TimerNode {
    TimerNode* prev;       // +0x00
    TimerNode* next;       // +0x04
    uint8_t  isActive;     // +0x08 (0 = inactive, 1 = active)
    uint8_t  counter;      // +0x09 (decremented each update)
    // padding to 0x0C
};

// Timer manager singleton structure
struct TimerManager {
    uint32_t   unknown0;   // +0x00 (possibly flags or count)
    TimerNode* head;       // +0x04
    TimerNode* tail;       // +0x08
    TimerNode* freeHead;   // +0x0C (alternate list head, used when main list empties)
};

// Global pointer to the singleton timer manager
extern TimerManager* g_timerManager;  // DAT_01205568

// Forward declaration of per-node update routine (decrements counter and returns something)
extern void updateTimerNode(TimerNode* node);  // FUN_0056f4b0

// Returns total number of nodes processed (both active and removed)
int32_t EventScheduler::updateTimers() {
    TimerManager* mgr = g_timerManager;
    int32_t processed = 0;
    TimerNode* currentNode = mgr->head;

    while (currentNode != nullptr) {
        processed++;
        if (currentNode != nullptr) {
            // Call per-node update (may modify additional state)
            updateTimerNode(currentNode);

            // Decrement the counter
            currentNode->counter--;

            // Remove node if it's inactive and counter reached zero
            if (currentNode->isActive == 0 && currentNode->counter == 0) {
                TimerNode* prev = currentNode->prev;
                TimerNode* next = currentNode->next;

                // Unlink from doubly linked list
                if (prev != nullptr) {
                    prev->next = next;
                }
                if (next != nullptr) {
                    next->prev = prev;
                }

                // Update head/tail pointers
                if (next == nullptr) {
                    mgr->tail = mgr->head;
                    mgr->head = prev;
                    if (prev == nullptr) {
                        mgr->tail = mgr->freeHead;  // fallback to alternate list tail
                    }
                } else {
                    next->prev = prev;
                }
            }
        }
        // Move to next node in the list
        currentNode = mgr->head;
    }

    return processed;
}