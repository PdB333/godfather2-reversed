// FUNC_NAME: EventQueue::pushEvent

// Function address: 0x00609980
// Role: Pushes an event into a small static event queue (max 8 entries).
// The queue is used for deferred processing or logging.
// Structure offsets documented in comments.

struct EventQueueEntry {
    int32_t status;  // +0x00 (set to 1 on push)
    int32_t param1;  // +0x04
    int32_t param2;  // +0x08
    char pad[0x0C];  // +0x0C (unused, total size 0x18)
};

// Global state (from Ghidra symbols)
static EventQueueEntry g_eventQueue[8]; // base at 0x01205770
static int32_t g_eventQueueCount;        // at 0x00F15A6C

void pushEvent(int32_t param1, int32_t param2) {
    if (g_eventQueueCount < 8) {
        int32_t index = g_eventQueueCount;
        g_eventQueueCount++;
        g_eventQueue[index].status = 1;
        g_eventQueue[index].param1 = param1;
        g_eventQueue[index].param2 = param2;
    }
}