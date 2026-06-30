// FUNC_NAME: addPendingEvent
// Address: 0x00609980
// This function queues up to 8 pending events with two integer parameters.
// It stores them in a fixed-size global buffer. Called from event processing code.

#define MAX_PENDING_EVENTS 8

struct PendingEvent {
    int32_t active;      // +0x00: 1 if slot is used
    int32_t param1;      // +0x04: first parameter
    int32_t param2;      // +0x08: second parameter
    // +0x0C to +0x17: unused padding (stride = 0x18)
};

static PendingEvent g_pendingEvents[MAX_PENDING_EVENTS];
static int32_t g_pendingCount = 0;

void addPendingEvent(int32_t param1, int32_t param2)
{
    if (g_pendingCount < MAX_PENDING_EVENTS) {
        int32_t slot = g_pendingCount;
        g_pendingEvents[slot].active = 1;
        g_pendingEvents[slot].param1 = param1;
        g_pendingEvents[slot].param2 = param2;
        g_pendingCount++;
    }
}