// FUNC_NAME: MessageBuffer::processMessages
// Function address: 0x004c0860
// Role: Iterates through a serialized message buffer, dispatching each message to a registered handler if it passes a bitmask filter.

#include <cstdint>

// Forward declaration of a function that looks up handler info for a message type
// Returns pointer to a vtable-like structure if found, and sets outMask to a bitmask for filtering.
extern void* __cdecl getHandlerForType(uint32_t typeId, uint32_t* outMask);

class MessageBuffer {
public:
    // +0x18: int totalMessageSize
    // +0x1c: uint8_t* bufferStart (raw data)
    // +0x20: int bytesRemaining
    // +0x24: uint8_t* readPosition

    bool processMessages(uint32_t filterMask);
};

// A 12-byte header preceding each message
struct MessageHeader {
    uint32_t typeId;   // +0x00: message type identifier
    uint32_t reserved; // +0x04: unused?
    uint32_t payloadSize; // +0x08: size of the following payload
};

// __thiscall: 'this' passed in ECX (or ESI from decompiler's unaff_ESI)
bool MessageBuffer::processMessages(uint32_t filterMask) {
    bool processedAny = false;

    if (this->bufferStart != nullptr) {
        // Skip first 4 bytes (might be a magic number or version)
        this->readPosition = this->bufferStart + 4;
        this->bytesRemaining = this->totalMessageSize - 4;

        while (this->bytesRemaining > static_cast<int>(sizeof(MessageHeader))) {
            // Save processed flag before this iteration (for return value)
            bool prevProcessed = processedAny;

            // Read the 12-byte header
            MessageHeader* header = reinterpret_cast<MessageHeader*>(this->readPosition);
            this->bytesRemaining -= sizeof(MessageHeader);
            this->readPosition += sizeof(MessageHeader);

            // Payload size (aligned to 4 bytes)
            uint32_t alignedPayloadSize = (header->payloadSize + 3) & ~3U;

            if (alignedPayloadSize <= static_cast<uint32_t>(this->bytesRemaining)) {
                // Advance read position past this payload
                this->readPosition += alignedPayloadSize;
                this->bytesRemaining -= alignedPayloadSize;

                // Lookup handler for this type
                uint32_t handlerMask;
                void* handlerVtable = getHandlerForType(header->typeId, &handlerMask);

                if (handlerVtable != nullptr) {
                    // Check if filter mask matches
                    if ((handlerMask & filterMask) != 0) {
                        // Call the handler's size validation function (vtable[1])
                        int expectedSize = reinterpret_cast<int(*)(uint32_t)>(*(void**)handlerVtable + 4)(header->typeId);
                        if (header->payloadSize == expectedSize) {
                            // Call the actual processing function (vtable[2])
                            reinterpret_cast<void(*)(uint32_t, uint8_t*, uint32_t)>(*(void**)handlerVtable + 8)(
                                header->typeId,
                                reinterpret_cast<uint8_t*>(header) + sizeof(MessageHeader),
                                header->payloadSize);
                            processedAny = true;
                        }
                    }
                }
            }

            // Update remaining for loop condition (re-read from member)
            if (this->bytesRemaining <= 12)
                return prevProcessed; // Return processed flag from start of this iteration
        }
    }

    return processedAny;
}