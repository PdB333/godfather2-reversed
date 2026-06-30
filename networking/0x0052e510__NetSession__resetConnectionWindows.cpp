// FUNC_NAME: NetSession::resetConnectionWindows

// Function address: 0x0052e510
// Resets the packet window slots and associated data for the networking layer (32-slot TNL window).
// Clears the packet history arrays and frees any existing packet buffer.

#include <cstdint>

// Global data structures (inferred from memory layout)
struct PacketWindowSlot {
    uint32_t field0;   // +0x00
    uint32_t field4;   // +0x04
    uint32_t field8;   // +0x08
    uint32_t fieldC;   // +0x0C
    uint32_t field10;  // +0x10
    uint32_t field14;  // +0x14
};
STATIC_ASSERT(sizeof(PacketWindowSlot) == 24);

// Array of 32 packet window slots (main data)
extern PacketWindowSlot g_packetWindowSlots[32];           // DAT_01219390

// Template array used to initialize the duplicate structure
extern const PacketWindowSlot g_packetWindowTemplate[32];  // DAT_0121939c

// Secondary arrays (likely sequence numbers, acknowledgement flags, or timestamps)
extern uint32_t g_secondaryArray1[32];                     // DAT_01219708
extern uint32_t g_secondaryArray2[32];                     // DAT_01219788 (will be filled from template)
extern uint32_t g_secondaryArray3[32];                     // DAT_01219808

// Global flags/state
extern int32_t g_connectionState;                          // DAT_01219828
extern int32_t g_sequenceNumber;                           // DAT_0121982C
extern int32_t g_acknowledgement;                          // DAT_01219830
extern int32_t g_retransmitTimeout;                        // DAT_01219834
extern int32_t g_remotePacketLoss;                         // DAT_01219838
extern int32_t g_localPacketLoss;                          // DAT_0121983C
extern int32_t g_roundTripTime;                            // DAT_01219840
extern int32_t g_bandwidth;                                // DAT_01219844
extern int32_t g_windowSize;                               // DAT_01219848
extern int32_t g_nextSequence;                             // DAT_0121984C
extern int32_t g_lastReceived;                             // DAT_01219850
extern int32_t g_sendQueueLength;                          // DAT_01219854
extern int8_t  g_flags;                                    // DAT_01219858
extern int8_t  g_connectionActive;                         // DAT_01219859

// External buffer pointer (freed on reset)
extern void* g_packetBuffer;                               // DAT_01205524

// External release function
void releasePacketBuffer(void* buffer, int32_t flag);      // FUN_006065a0

void NetSession::resetConnectionWindows(void)
{
    PacketWindowSlot* slotPtr = g_packetWindowSlots;
    int32_t slotCount = 32;
    
    // Clear all 32 packet window slots
    do {
        slotPtr->field0   = 0;
        slotPtr->field4   = 0;
        slotPtr->field8   = 0;
        slotPtr->fieldC   = 0;
        slotPtr->field10  = 0;
        slotPtr->field14  = 0;
        slotPtr++;
        slotCount--;
    } while (slotCount != 0);
    
    // Reset global state variables
    g_connectionState     = 0;
    g_sequenceNumber      = 0;
    g_acknowledgement     = 0;
    g_retransmitTimeout   = 0;
    g_remotePacketLoss    = 0;
    g_localPacketLoss     = 0;
    g_roundTripTime       = 0;
    g_bandwidth           = 0;
    g_windowSize          = 0;
    g_nextSequence        = 0;
    g_lastReceived        = 0;
    g_sendQueueLength     = 0;
    g_flags               = 0;
    g_connectionActive    = 0;
    
    // Initialize secondary arrays: clear two, copy one from template
    int32_t idx = 0;
    uint32_t srcOffset = 0;
    do {
        g_secondaryArray1[idx] = 0;
        // Copy 24-byte block from template (each element 0x18 bytes)
        g_secondaryArray2[idx] = *(uint32_t*)((uint8_t*)g_packetWindowTemplate + srcOffset);
        g_secondaryArray3[idx] = 0;
        
        srcOffset += 0x18;
        idx++;
    } while (srcOffset < 0x300);  // 32 * 0x18 = 0x300
    
    // Release any existing packet buffer
    if (g_packetBuffer != nullptr) {
        releasePacketBuffer(g_packetBuffer, 0);
    }
    g_packetBuffer = nullptr;
}