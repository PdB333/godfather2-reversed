// FUNC_NAME: TimerManager::update

//=============================================================================
// Function: 0x0056fbb0
// Role: Timer/Event Manager update tick.
// Processes a linked list of timed callbacks. Each timer has a counter byte at
// offset +9 that is decremented once per frame. If the timer's active flag at
// offset +8 is zero and the counter reaches zero, the timer is removed from
// the list and freed (via a callback function). The global at 0x01205568
// points to a struct managing the list head/tail.
//=============================================================================

#include <cstdint>

// Node structure for a timer event.
// Offsets relative to node pointer:
//   +0x00: next  (pointer to next node)
//   +0x04: prev  (pointer to previous node)
//   +0x08: activeFlag (bool, 0 = inactive)
//   +0x09: counter (uint8, decremented each frame)
//   +0x0A: ...    (possibly more data, e.g. callback function pointer)
struct TimerEventNode {
    TimerEventNode* next;       // +0x00
    TimerEventNode* prev;       // +0x04
    int8_t          activeFlag; // +0x08
    uint8_t         counter;    // +0x09
    // (other fields not used in this function)
};

// Global timer manager state.
// Offset layout at 0x01205568:
//   +0x00: unknown
//   +0x04: head (pointer to first node)
//   +0x08: tail (pointer to last node)
//   +0x0C: sentinel (probably dummy node for list termination)
struct TimerManagerData {
    char           pad_0[4];       // +0x00
    TimerEventNode* head;          // +0x04
    TimerEventNode* tail;          // +0x08
    TimerEventNode* sentinel;      // +0x0C
};

// Forward declaration of the timer action callback.
// This is called before decrementing the counter.
void TimerEvent_TickAction(TimerEventNode* node);

// Global data pointer (set during initialization).
extern TimerManagerData* g_timerManagerData; // 0x01205568

//-------------------------------------------------------------------------
// TimerManager::update()
// Iterates over all timer nodes once per frame, decrements counters, and
// removes expired timers.
// Returns the number of nodes processed.
//-------------------------------------------------------------------------
int TimerManager::update()
{
    TimerManagerData* mgr = g_timerManagerData; // DAT_01205568
    int processedCount = 0;

    // Start from the head.
    TimerEventNode* node = mgr->head;

    while (node != nullptr) {
        processedCount++;

        // Call the tick action (e.g., check conditions, play sound, etc.)
        TimerEvent_TickAction(node);

        // Decrement the counter.
        node->counter--;

        // If the timer is not active (flag) and counter reached zero, remove it.
        if ((node->activeFlag == '\0') && (node->counter == '\0')) {
            TimerEventNode* next = node->next;      // save next
            TimerEventNode* prev = node->prev;      // save prev

            // Unlink the node from the doubly-linked list.
            if (next != nullptr) {
                next->prev = prev;                 // next->prev = prev
            }
            if (prev == nullptr) {
                // Removing head node.
                mgr->head = next;                  // head = next
                if (next == nullptr) {
                    // List is now empty: tail = sentinel.
                    mgr->tail = mgr->sentinel;
                }
            } else {
                prev->next = next;                 // prev->next = next
            }
            // Note: The removed node is presumably freed elsewhere (or reused).
        }

        // After any removal, restart iteration from the head.
        // This is typical for safe linked list traversal during modification.
        node = mgr->head;
    }

    return processedCount;
}