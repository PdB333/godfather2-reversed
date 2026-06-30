// FUNC_NAME: EventScheduler::clearAllEvents
// Address: 0x00606470
// Clears an array of 20 event slots. For each non-zero slot, releases the event data and resets the slot.

#include <cstdint>

// Global array of event slot handles (likely pointers or IDs)
extern uint32_t g_eventSlots[20];

// Internal release function for a single slot (defined elsewhere)
void releaseEventSlot();

void EventScheduler::clearAllEvents()
{
    uint32_t slotIndex = 0;
    do {
        // Check if slot contains a valid event (non-zero handle)
        if (g_eventSlots[slotIndex] != 0) {
            // Release the event associated with this slot
            releaseEventSlot();
            // Clear the slot to indicate it's free
            g_eventSlots[slotIndex] = 0;
        }
        slotIndex++;
    } while (slotIndex < 20);
}