// FUNC_NAME: StreamManager::prepareBufferForWrite

#include <cstdint>

class StreamManager {
public:
    // Structure at this+0x14 points to a BufferDescriptor
    struct BufferDescriptor {
        int32_t field_0;    // +0x0
        int32_t writeOffset; // +0x4
    };

private:
    uint8_t  unknown_00[0x08]; // 0x00-0x07
    int32_t  m_readOffset;   // +0x08
    uint8_t  unknown_0C[0x08]; // 0x0C-0x13
    BufferDescriptor* m_pBufferDesc; // +0x14
    int32_t  m_dataEnd;      // +0x18
    int32_t  m_bufferBase;   // +0x1c
    uint8_t  unknown_20[0x11]; // 0x20-0x30
    uint8_t  m_bInCallback;  // +0x31 (bool flag)
    uint8_t  unknown_32[0x0A]; // 0x32-0x3B
    void (*m_pfnCallback)(); // +0x3c (function pointer)

public:
    void FUN_00635d00(); // the function at 0x00635d00
};

// Forward declaration of callee (not fully reversed)
void ensureSpaceAvailable(StreamManager* this); // FUN_00635c70

// Implementation
void StreamManager::FUN_00635d00() {
    void (*callback)() = m_pfnCallback;

    // Only proceed if callback is valid and the flag allows
    if (callback != nullptr && m_bInCallback != 0) {
        int32_t originalRead = m_readOffset;
        int32_t originalBase = m_bufferBase;
        int32_t originalWrite = m_pBufferDesc->writeOffset;

        // Check if there is enough room for 0xA0 bytes (160 bytes)
        if (m_dataEnd - m_readOffset < 0xA0) {
            ensureSpaceAvailable(this); // expand buffer if needed
        }

        // Set write pointer to read offset + 0xA0 block
        m_pBufferDesc->writeOffset = m_readOffset + 0xA0;

        // Enter callback: temporarily disable reentrancy
        m_bInCallback = 0;
        (*callback)();
        m_bInCallback = 1;

        // Restore write offset to original position relative to base
        m_pBufferDesc->writeOffset = m_bufferBase + (originalWrite - originalBase);

        // Advance read offset by the data callback consumed (original delta)
        m_readOffset = m_bufferBase + (originalRead - originalBase);
    }
}