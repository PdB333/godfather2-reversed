// FUNC_NAME: EventSystem::SendEvent
// Address: 0x00489ee0
// Role: Prepares and sends an event message with optional string payload.
// This function marshals arguments from various sources and calls an internal dispatcher.

#include <cstdint>

// Forward declaration of the internal send function
void InternalSendEvent(uint64_t target, uint64_t data, uint64_t extra, uint64_t flags,
                       const char* string, int stringLen, int alwaysOne);

void __fastcall EventSystem::SendEvent(int* messageType, const uint64_t* extraData,
                                       const uint64_t* target, uint32_t dataLow,
                                       uint32_t dataHigh, const char* string)
{
    // Combine the two 32-bit data pieces into a 64-bit value (data payload)
    uint64_t dataPayload = (static_cast<uint64_t>(dataHigh) << 32) | dataLow;

    // Build flags from messageType pointer
    uint64_t flags = 0;
    if (messageType != nullptr) {
        // High 32 bits = 2 (message type indicator?), low 32 bits = *messageType
        flags = (static_cast<uint64_t>(2) << 32) | *messageType;
    }

    // Optional extra data (if provided)
    uint64_t extra = 0;
    if (extraData != nullptr) {
        extra = *extraData;
        // Set bit 32 in flags to indicate extra data present
        flags |= (static_cast<uint64_t>(1) << 32);
    }

    // Calculate string length including null terminator
    int stringLen = 0;
    if (string != nullptr) {
        const char* p = string;
        while (*p != '\0') {
            ++p;
        }
        stringLen = (p - string) + 1;  // include terminating null
    }

    // Call the internal send routine
    // First argument is the dereferenced 64-bit target
    InternalSendEvent(*target, dataPayload, extra, flags, string, stringLen, 1);
}