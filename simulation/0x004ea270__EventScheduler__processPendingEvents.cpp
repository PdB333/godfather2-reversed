// FUNC_NAME: EventScheduler::processPendingEvents

// Reconstructed from 0x004ea270 - Processes pending events from the event queue and dispatches them.
// Uses thread-local storage (FS:[0x2c]) to get the current game context.
// Global pointers DAT_0122339c and DAT_012233a0 likely point to the EventScheduler singleton.

#include <cstdint>

// Forward declarations
class EventScheduler;
extern EventScheduler* g_eventScheduler; // DAT_0122339c
extern int32_t g_eventSchedulerFlag;     // DAT_012233a0 (maybe a flag or secondary pointer)
extern int32_t* g_commandBuffer1;        // DAT_01206880
extern int32_t* g_commandBuffer2;        // DAT_012068e8
extern int32_t* g_altCommandBuffer1;     // DAT_012054ec
extern int32_t* g_altCommandBuffer2;     // DAT_012054f0

// External functions
void EventScheduler::lock();             // FUN_004ea080
void EventScheduler::dispatchEvent(int32_t context, int32_t eventId, int32_t flag, int32_t param, int32_t a5, int32_t a6, int32_t type); // FUN_004ea560

// Thread-local storage: FS:[0x2c] points to a TLS array; first slot holds a pointer to the current game context.
// The game context has fields at offsets:
// +0x24: currentEventId (int32_t)
// +0x34: useAltBufferFlag (int32_t)
// +0x154: pendingEventCount (int32_t)
// +0x158: pendingEventId (int32_t) - last event ID from the queue

void EventScheduler::processPendingEvents(int32_t context) {
    lock();

    if (g_eventScheduler == nullptr || g_eventSchedulerFlag == 0) {
        // No global scheduler; use thread-local context directly.
        int32_t** tlsArray = reinterpret_cast<int32_t**>(__readfsdword(0x2c));
        int32_t* gameContext = *tlsArray; // First TLS slot
        int32_t currentEventId = *(gameContext + 0x24 / 4); // +0x24

        if (currentEventId != 0) {
            dispatchEvent(context, currentEventId, 0, 0xFFFFFFFF, 0, 0, 2);

            int32_t* commandBuffer = g_commandBuffer1;
            if (*(gameContext + 0x34 / 4) != 0) {
                commandBuffer = g_commandBuffer2;
            }

            // Push two values onto the command buffer (like a stack)
            int32_t** bufferPtr = reinterpret_cast<int32_t**>(commandBuffer + 0x14 / 4);
            **bufferPtr = reinterpret_cast<int32_t>(&PTR_LAB_01124bd0); // Some constant/label
            *bufferPtr += 1;
            **bufferPtr = currentEventId;
            *bufferPtr += 1;
        }
    } else {
        // Use global scheduler's event queue.
        int32_t eventCount = *(g_eventScheduler + 0x154 / 4); // +0x154
        if (eventCount > 0) {
            int32_t* eventArray = reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_eventScheduler) + 0x158); // +0x158
            for (int32_t i = 0; i < eventCount; ++i) {
                int32_t eventId;
                if (*(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_eventScheduler) + 0x154)) == 0) {
                    // Use thread-local context's current event
                    int32_t** tlsArray = reinterpret_cast<int32_t**>(__readfsdword(0x2c));
                    int32_t* gameContext = *tlsArray;
                    eventId = *(gameContext + 0x24 / 4);
                } else {
                    // Use a field from the event array element (negative offset -0x51*4 = -0x144)
                    eventId = *(eventArray - 0x51); // piVar4[-0x51]
                }

                if (eventId != 0 && *eventArray != -1) {
                    dispatchEvent(context, eventId, 1, *eventArray, 0, 0, 2);
                }
                ++eventArray;
            }
        }

        // Handle a final event from the thread-local context
        int32_t** tlsArray = reinterpret_cast<int32_t**>(__readfsdword(0x2c));
        int32_t* gameContext = *tlsArray;
        int32_t useAlt = *(gameContext + 0x34 / 4);
        int32_t* altBuffer = g_altCommandBuffer1;
        if (useAlt != 1) {
            altBuffer = g_altCommandBuffer2;
        }
        if (altBuffer != nullptr) {
            int32_t finalEventId = *(reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_eventScheduler) + 0x158));
            dispatchEvent(context, altBuffer, 0, finalEventId, 0, 0, 2);
        }
    }
}