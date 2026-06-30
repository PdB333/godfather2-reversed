// FUNC_NAME: TNLMessageQueue::enqueueMessage
// Address: 0x00495510
// Role: Enqueues a message into a per-channel ring buffer, manages sequence numbers, and triggers batch processing.
// Structure sizes: entry size = 0x1c (28 bytes), channel stride = 0x80 (128 bytes)

#include <cstdint>

// Forward declarations or external references
extern void FUN_00459280(void*); // Process/completion callback for old sequence entry
extern void FUN_00ab51e0(int);   // Batch processing trigger

// Global arrays (likely part of a manager singleton)
extern uint32_t g_channelSeqCounter[/* ??? */];      // DAT_01217b00, offset per channel: 0x80 bytes
extern uint8_t* g_channelRingBuffer[/* ??? */];      // DAT_01217d24, pointer to buffer per channel (4 bytes each)
extern uint32_t g_channelRingSize[/* ??? */];        // DAT_01217d14, ring buffer size per channel (4 bytes each)
extern int32_t g_pendingMessageCount;                // DAT_01217d38, global count of pending messages
extern int32_t g_batchProcessingFlag;                // DAT_01217d34, non-zero enables batch processing
extern void* g_lockObject;                           // LOCK/UNLOCK macros (assume a global mutex)

// LOCK/UNLOCK wrapper (assumes some platform-specific primitive)
void LOCK();
void UNLOCK();

// Enqueue a 5-dword message into the specified channel's ring buffer.
// @param outResult - output: outResult[0] = sequence number, outResult[1] = channel index
// @param arg2      - message field 1 (offset +4)
// @param arg3      - message field 2 (offset +8)
// @param arg4      - message field 3 (offset +0xC)
// @param arg5      - message field 4 (offset +0x10)
// @param arg6      - message field 0 / type (offset +0)
// @param channel   - channel index (0-based)
void TNLMessageQueue::enqueueMessage(uint32_t outResult[2],
                                     uint32_t arg2,
                                     uint32_t arg3,
                                     uint32_t arg4,
                                     uint32_t arg5,
                                     uint32_t arg6,
                                     uint32_t channel)
{
    // Retrieve current sequence counter for this channel
    uint32_t seq = *(uint32_t*)((uint8_t*)g_channelSeqCounter + channel * 0x80);
    
    // Compute index into the ring buffer: seq % size
    uint32_t ringIndex = seq % g_channelRingSize[channel];
    
    // Pointer to the ring buffer base for this channel
    uint8_t* ringBase = g_channelRingBuffer[channel];
    // Entry offset: ringIndex * 0x1c
    uint32_t entryOffset = ringIndex * 0x1c;
    uint8_t* entry = ringBase + entryOffset;
    
    // Read the old value at offset 0x14 (the previous sequence? something to process)
    uint32_t oldSeqOrData = *(uint32_t*)(entry + 0x14);
    // Process that old value (e.g., acknowledge/discard)
    FUN_00459280(&oldSeqOrData);
    
    // Lock and update the sequence field in the entry
    LOCK();
    *(uint32_t*)(entry + 0x14) = seq;
    UNLOCK();
    
    // Write the message fields into the entry
    *(uint32_t*)(entry + 0x00) = arg6;     // type/field0
    *(uint32_t*)(entry + 0x04) = arg2;     // field1
    *(uint32_t*)(entry + 0x08) = arg3;     // field2
    *(uint32_t*)(entry + 0x0C) = arg4;     // field3
    *(uint32_t*)(entry + 0x10) = arg5;     // field4
    
    // Advance the channel sequence counter (atomic increment)
    LOCK();
    (*(int32_t*)((uint8_t*)g_channelSeqCounter + channel * 0x80))++;
    UNLOCK();
    
    // Increment global pending message count
    LOCK();
    int32_t newPendingCount = g_pendingMessageCount + 1;
    UNLOCK();
    g_pendingMessageCount = newPendingCount;
    
    // If batch processing is enabled, zero the counter and trigger processing
    if (g_batchProcessingFlag != 0) {
        LOCK();
        g_pendingMessageCount = 0;
        UNLOCK();
        if (newPendingCount != 0) {
            FUN_00ab51e0(newPendingCount);
        }
    }
    
    // Write output
    outResult[1] = channel;
    outResult[0] = seq;
}