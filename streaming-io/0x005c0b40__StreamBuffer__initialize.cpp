// FUNC_NAME: StreamBuffer::initialize

// Reconstructed constructor/initializer for network stream buffer structure.
// Called by various packet management functions to set up a buffer.
// Uses global singleton init flag (DAT_01205664) to ensure one-time module setup.

#include <cstdint>

// External helper functions assumed from other parts of the codebase.
extern void StreamBuffer_StaticInit();    // 0x005c39d0
extern void StreamBuffer_ResetInternal(); // 0x005c28c0
extern uint32_t StreamBuffer_AllocateBuffer(uint32_t previousBuffer, int32_t, uint32_t size, uint32_t* outFlags, int32_t* outStatus); // 0x005c27a0

// Global flag for one-time initialization.
extern uint32_t g_StreamBufferGlobalsInitialized; // DAT_01205664

// Structure layout for the stream buffer.
// Offsets in comments relative to param_1 pointer.
struct StreamBuffer {
    uint32_t bufferPtr;       // +0x00: pointer to allocated raw data buffer (or handle)
    uint32_t someZero;        // +0x04: always zeroed after init
    int32_t  bufferSize;      // +0x08: requested buffer size, negative means do allocation
    uint32_t anotherZero;     // +0x0C: always zeroed
    uint32_t yetAnotherZero;  // +0x10: always zeroed
    uint8_t  initialized;     // +0x14: set to 1 at the end
};

void __fastcall StreamBuffer::initialize(StreamBuffer* thisPtr)
{
    // One-time global initialization for the stream buffer module.
    if (g_StreamBufferGlobalsInitialized == 0) {
        StreamBuffer_StaticInit();
    }

    // Reset internal state (likely clears some global counters or pools).
    StreamBuffer_ResetInternal();

    // If the stored buffer size is negative, allocate a new buffer of size 0xC (12 bytes).
    if (thisPtr->bufferSize < 0) {
        uint32_t newBuffer = StreamBuffer_AllocateBuffer(
            thisPtr->bufferPtr,
            0,
            0xC,
            &thisPtr->something,  // note: param_1+1 is used as an output flags field
            &thisPtr->bufferSize
        );
        thisPtr->bufferPtr = newBuffer;
    }

    // Zero out several fields.
    thisPtr->someZero       = 0;
    thisPtr->yetAnotherZero = 0;
    thisPtr->anotherZero    = 0;

    // Mark the buffer as initialized.
    thisPtr->initialized = 1;
}