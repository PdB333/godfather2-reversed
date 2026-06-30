// FUNC_NAME: NetSendBuffer::pushPacket
// Address: 0x6281d0
// This function pushes a packet (8 bytes) into a circular send buffer.
// The buffer structure has write pointer at offset +0x08 and base at +0x0c.
// 'index' is a sequence number or slot index used to locate the source data.
// The function copies 8 bytes from a computed source to the current write head,
// then advances the head by 8 and marks the written element as committed.

// Assumed structure (from offsets):
// struct NetSendBuffer {
//     DWORD* writePtr;   // +0x08
//     DWORD* basePtr;    // +0x0c
// };

// The function is a static helper; 'buf' is the buffer pointer passed in EDX
// and 'index' is a register value passed in EAX.

#include <cstdint>

int __fastcall NetSendBuffer_pushPacket(int index, NetSendBuffer* buf)
{
    uint32_t* sourcePtr;
    uint32_t* destPtr;
    int newIndex;
    bool valid;

    // Check if index is within a valid range (0 .. 9999 after wrapping?)
    valid = (index + 9999U) < 10000U;  // Equivalent to (index <= 0) due to unsigned wrap
    if (valid) {
        // Recompute index: add 1 + (number of elements currently in buffer)
        newIndex = index + 1 + ((buf->writePtr - buf->basePtr) >> 3);
    } else {
        newIndex = index;  // unchanged? But variable scope; in code this path doesn't reassign.
    }

    // Call some validation function (e.g., mutex lock or state check)
    if (FUN_00625f80() != 0) {
        // Additional validation for buffer state
        if (FUN_00628120(buf) != 0) {
            // Determine source address: if newIndex < 1, get from a special pool,
            // otherwise compute from base + (newIndex - 1) * 8
            if (newIndex < 1) {
                sourcePtr = (uint32_t*)FUN_00625430();   // allocate/fetch source
            } else {
                sourcePtr = (uint32_t*)(buf->basePtr + ((newIndex - 1) * 2));  // each element 8 bytes (2 uint32)
            }

            // Copy 8 bytes from source to current write head
            destPtr = (uint32_t*)buf->writePtr;
            destPtr[0] = sourcePtr[0];
            destPtr[1] = sourcePtr[1];

            // Advance write pointer by 8 bytes
            buf->writePtr = (uint32_t*)((uint8_t*)buf->writePtr + 8);

            // Mark the element just before the one just written as committed? (This is unclear)
            FUN_006362d0(buf, (uint32_t*)((uint8_t*)buf->writePtr - 0x10), 1);

            return 1;  // success
        }
    }
    return 0;  // failure
}