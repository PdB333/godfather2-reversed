// FUNC_NAME: Deserializer::readAndDispatch
#include <cstdint>

// Function at 0x005d70e0: Reads a serialized message from an internal buffer and dispatches it to a handler.
// The object (this) has a pointer at +0x18 to the current read position in a buffer.
// The format: 4 header words (type, flags, payloadSize, alignment), then payload aligned to alignment boundary,
// then a footer word. The callback receives all extracted data.
typedef void (__cdecl *MessageHandler)(uint32_t msgType, uint32_t msgFlags, uint64_t payloadInfo, uint32_t alignment, uint32_t footer);

void __thiscall Deserializer::readAndDispatch(MessageHandler* handlerPtr) {
    // Fetch and align the current read pointer
    uint32_t* readPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(*(uint32_t*)(this + 0x18)) + 3 & ~3);
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(readPtr);

    // Read the 4 header fields
    uint32_t msgType = *readPtr;
    readPtr++;
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(readPtr);

    uint32_t msgFlags = *readPtr;
    readPtr++;
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(readPtr);

    uint32_t payloadSize = *readPtr;   // size of the payload data
    readPtr++;
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(readPtr);

    uint32_t alignment = *readPtr;     // alignment requirement for payload start
    readPtr++;
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(readPtr);

    // Compute the aligned payload start address
    uint32_t payloadStart = (reinterpret_cast<uint32_t>(readPtr) + alignment + 0xF) & ~(alignment - 1);

    // Advance past the payload (rounded up to 4 bytes)
    uint32_t* payloadEnd = reinterpret_cast<uint32_t*>(
        (payloadSize + 3 & ~3) + payloadStart
    );
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(payloadEnd);

    // Read the footer word (after payload)
    uint32_t footer = *payloadEnd;
    *(uint32_t*)(this + 0x18) = reinterpret_cast<uint32_t>(payloadEnd + 1);

    // Build the 64-bit payload info: high 32 = payloadSize, low 32 = payloadStart (if payloadSize != 0, else 0)
    uint64_t payloadInfo = (static_cast<uint64_t>(payloadSize) << 32) |
                           (payloadSize != 0 ? payloadStart : 0);

    // Call the user-supplied handler
    (*handlerPtr)(msgType, msgFlags, payloadInfo, alignment, footer);
}