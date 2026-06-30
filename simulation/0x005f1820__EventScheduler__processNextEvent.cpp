// FUNC_NAME: EventScheduler::processNextEvent
// Function at 0x005f1820: iterates a global linked list of events and executes the first one that is ready
// (not currently executing, not blocked, and activation time <= currentTime). Returns 1 if processed, 0 otherwise.

#include <cstdint>

// Structure of a node in the event list
struct EventNode {
    EventNode* next;                // +0x00 (next pointer)
    void*     dataBlock;            // +0x08 (pointer to another structure with flags at offset 0x08)
    float     activationTime;       // +0x50 (time when event becomes eligible)
    int32_t   state;                // +0x68 (1 = currently executing, other values available)
};

// Global head of the event list
extern EventNode* g_eventHead;      // DAT_011a0ef4

// Called to process an event node
void processScheduledEvent(EventNode* node); // FUN_005f1ef0

uint8_t eventScheduler_tick(float currentTime)
{
    EventNode* pNode = g_eventHead;
    if (pNode == nullptr) {
        return 0;
    }

    while (true) {
        bool bSkip = (pNode->state == 1);                              // state == running?
        if (!bSkip) {
            uint8_t flags = *(uint8_t*)((uint8_t*)pNode->dataBlock + 8); // flags at offset 8
            bSkip = (flags & 0x10) != 0;                               // bit 4 set = blocked?
        }
        if (!bSkip) {
            bSkip = (currentTime < pNode->activationTime);             // not yet time?
        }

        if (bSkip) {
            // Not eligible – advance to next node
            pNode = pNode->next;
            if (pNode == nullptr) {
                return 0;
            }
        } else {
            // Eligible – process it
            processScheduledEvent(pNode);
            return 1;
        }
    }
}