// FUNC_NAME: StreamManager::shutdownActiveStream

#include <cstdint>

// Forward declarations for external engine functions
extern void shutdownBankStream(void*);
extern void releaseStreamHandle(void*);
extern void closeStreamHandle(void*);
extern void detachStreamObject(void* parent, void* child);

// StreamManager class (hypothetical structure based on offsets)
class StreamManager {
public:
    // +0x5c: flags (bit0 = pendingShutdown, bit1 = isMultiTrack)
    uint32_t flags; 

    // +0x68: base pointer for stream object (used as 'this' for detach)
    uint8_t padding1[0x68 - 0x5c - sizeof(uint32_t)]; 

    // +0x68: some object handle/pointer
    void* streamObject;

    // ... unknown data ...

    // +0x868: pointer to a child stream entity
    void* childStream;

    // +0x86c: flag indicating child stream is active
    uint8_t childStreamActive;

    // ... rest of class ...

    // Member function: shutdown the currently active stream
    void shutdownActiveStream();
};

void StreamManager::shutdownActiveStream() {
    uint32_t oldFlags = this->flags;

    // Check if shutdown was requested (bit0)
    if ((oldFlags & 1) != 0) {
        // Clear the pending shutdown flag
        this->flags = oldFlags & 0xFFFFFFFE;

        if ((oldFlags & 2) == 0) {
            // Standard stream shutdown path
            shutdownBankStream(&DAT_0121bf38);  // global bank stream handle
            releaseStreamHandle(&DAT_0121bf38); // release bank stream resources
        } else {
            // Multi-track stream shutdown path
            shutdownBankStream(&DAT_012069c4);  // global track A handle
            shutdownBankStream(&DAT_012069d4);  // global track B handle
        }

        // If there is an active child stream, detach and release it
        if ((this->childStreamActive != 0) && (this->childStream != nullptr)) {
            detachStreamObject((this->streamObject), this->childStream);
            this->childStream = nullptr;
        }
        this->childStreamActive = 0;
    }
}