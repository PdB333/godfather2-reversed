// FUNC_NAME: writeEventToPacket
#include <cstdint>

// Global structures (addresses determined from cross-references)
struct EventManager {
    uint32_t field_0x00;          // +0x00
    uint32_t field_0x04;          // +0x04
    uint32_t field_0x08;          // +0x08
    uint32_t field_0x0c;          // +0x0c
    void** eventTypeArray;        // +0x10 array of pointers to event type descriptors
    uint32_t eventTypeCount;      // +0x14
};

struct OutputBuffer {
    uint32_t field_0x00;          // +0x00
    uint32_t field_0x04;          // +0x04
    uint32_t field_0x08;          // +0x08
    uint32_t field_0x0c;          // +0x0c
    uint32_t field_0x10;          // +0x10
    uint8_t* writePtr;            // +0x14 current write position inside the buffer
};

// Forward declarations of the global pointers (actual addresses resolved by linker)
extern EventManager* g_eventManager;    // DAT_0122349c
extern OutputBuffer* g_outputBuffer;    // DAT_01206880

// External references to vtable-like markers (addresses from .rdata)
extern uint32_t PTR_LAB_01123d28;   // Some type marker
extern uint32_t PTR_FUN_01123d64;   // Another type marker

// Event data structure (incoming parameter)
// Layout:
// +0x00: unknown
// +0x04: 64-bit value (e.g., timestamp or unique ID)
// +0x0c: byte flag indicating if already written
struct EventData {
    uint32_t unknown_0x00;  // +0x00
    uint64_t value64;       // +0x04
    uint8_t  writtenFlag;   // +0x0c
};

// __fastcall: ECX = param_1 (unused), EDX = eventData, stack = eventTypeId
uint32_t __fastcall writeEventToPacket(uint32_t param_1, EventData* eventData, uint32_t eventTypeId) {
    // NOTE: param_1 (ECX) is not used; possibly a leftover or this-pointer in some builds.
    // The original code uses the value of EAX on entry (in_EAX) – we ignore it as it’s likely a
    // leftover from the caller and not a real parameter.
    uint32_t result = 0;  // Default to failure

    if (g_eventManager->eventTypeCount != 0) {
        void** currentEventType = g_eventManager->eventTypeArray;
        uint32_t index = 0;

        // Search for an event type with matching ID
        while (*((uint32_t*)(*currentEventType)) != eventTypeId) {
            ++index;
            ++currentEventType;
            if (index >= g_eventManager->eventTypeCount) {
                return 0;  // Event type not found
            }
        }

        result = 1;  // Mark as success

        // If this instance hasn't been written yet, write a marker + the first 4 bytes of the value
        if (eventData->writtenFlag == 0) {
            // Write the vtable pointer (type descriptor) to the output buffer
            *((void**)g_outputBuffer->writePtr) = &PTR_LAB_01123d28;
            g_outputBuffer->writePtr += 4;

            // Write the low 4 bytes of the event's value
            *((uint32_t*)g_outputBuffer->writePtr) = static_cast<uint32_t>(eventData->value64);
            g_outputBuffer->writePtr += 4;

            // Mark as written
            eventData->writtenFlag = 1;
        }

        // Write a second marker + the full 8-byte value + the event type ID
        *((void**)g_outputBuffer->writePtr) = &PTR_FUN_01123d64;
        g_outputBuffer->writePtr += 4;

        // Align write pointer to 4-byte boundary
        uint8_t* alignedPtr = reinterpret_cast<uint8_t*>(
            (reinterpret_cast<uintptr_t>(g_outputBuffer->writePtr) + 3) & ~3
        );
        g_outputBuffer->writePtr = alignedPtr;

        // Write the 8-byte value
        *((uint64_t*)g_outputBuffer->writePtr) = eventData->value64;
        g_outputBuffer->writePtr += 8;

        // Write the event type ID
        *((uint32_t*)g_outputBuffer->writePtr) = eventTypeId;
        g_outputBuffer->writePtr += 4;
    }

    return result;
}