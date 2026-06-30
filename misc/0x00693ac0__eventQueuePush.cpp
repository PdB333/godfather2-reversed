// FUNC_NAME: eventQueuePush
#include <cstdint>

// Global event queue state
// Maximum number of queued events
static const int kMaxQueuedEvents = 4;

// Structure for an event entry (5 dwords total, 20 bytes)
struct EventQueueEntry {
    uint32_t field0; // Event type/ID (param_1)
    uint32_t field1; // Reserved
    uint32_t field2; // Reserved
    uint32_t field3; // Reserved
    uint32_t field4; // Reserved
};

// Global queue count (max 4)
static int g_eventQueueCount = 0;

// Global queue array, 4 entries, each 20 bytes
static EventQueueEntry g_eventQueue[4];

// Forward declaration of the subroutine that processes param_2
// Defined at 0x004d3d90
uint32_t ProcessEvent(uint32_t param_2);

/**
 * Pushes an event (param_1) into a fixed-size queue (max 4 entries).
 * Calls ProcessEvent with param_2 to handle the associated data.
 * Returns 1 on success, or an error code with the low byte cleared on failure.
 */
uint32_t eventQueuePush(uint32_t param_1, uint32_t param_2)
{
    // If queue is not full, store the event and process its data
    if (g_eventQueueCount < kMaxQueuedEvents) {
        // Store param_1 in the first field of the current queue entry
        g_eventQueue[g_eventQueueCount].field0 = param_1;

        // Process the second parameter (likely event data or context)
        ProcessEvent(param_2);

        // Increment the queue counter
        g_eventQueueCount++;

        // Indicate success
        return 1;
    }

    // Queue is full; increment the counter anyway (overflow?)
    g_eventQueueCount++;

    // Return an error code: clears the low byte of whatever was in EAX
    // (placeholder: actual error code would come from a previous operation)
    return 0;  // In the original, this was `in_EAX & 0xffffff00`
}