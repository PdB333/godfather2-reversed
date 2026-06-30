// FUNC_NAME: GameSession::flushReplicationUpdates

// Reconstructed C++ from Ghidra decompiled output at 0x0053d310
// Purpose: Flush pending replication updates (32-byte packet slots) to the network layer.

#include <cstdint>

// Forward declarations of called global functions
extern void lockMutex();                // FUN_00612a60
extern void sendReplicationData(uint32_t sourceId, uint32_t destId, void* buffer); // FUN_0060add0
extern void processReceivedAcks();      // FUN_0053d200
extern void flushOutputQueue();         // FUN_006063b0
extern void cleanupSentData();          // FUN_0053d590

// External globals
extern uint32_t g_localSessionId;       // DAT_01219908
extern uint32_t g_pendingReplicationTarget; // DAT_01219928

class GameSession {
public:
    // Offsets based on param_1:
    // +0x10: sessionId or connectionId
    // +0x14: localUserId or sourceId
    // +0x2a8: current replication slot index (each slot = 0x20 bytes)
    // +0xb0, 0xc0, 0xd0: buffers for outgoing replication data (likely three separate streams)

    void __thiscall flushReplicationUpdates() {
        lockMutex(); // Enter critical section

        // Check if we need to send a replication header
        if (*(uint32_t*)(this + 0x10) == g_localSessionId && g_pendingReplicationTarget != 0) {
            uint32_t headerBuffer[4] = {0}; // local_20 (4 uint32s)
            sendReplicationData(*(uint32_t*)(this + 0x10), g_pendingReplicationTarget, headerBuffer);
        }

        processReceivedAcks(); // Handle ACKs for reliable packets

        // Check and process up to 4 replication slots (indexed by current slot)
        uint32_t slotIndex = *(uint32_t*)(this + 0x2a8); // Index into array starting at offset 0xf0
        uint32_t* slotBase = (uint32_t*)(this + 0xf0 + slotIndex * 0x20); // Each slot is 20 bytes

        // Slot data fields:
        // +0x00: typeId (if !=0, need to send)
        // +0x04: objectId
        // +0x08: someFlag
        // +0x0c: anotherFlag

        uint32_t typeId = slotBase[0];    // offset +0x00
        if (typeId != 0) {
            // Send replication data using the first buffer (b0)
            sendReplicationData(*(uint32_t*)(this + 0x14), typeId, (void*)(this + 0xb0));
        }

        uint32_t objectId = slotBase[1];  // offset +0x04
        if (objectId != 0) {
            sendReplicationData(*(uint32_t*)(this + 0x14), objectId, (void*)(this + 0xc0));
        }

        uint32_t flagA = slotBase[2];     // offset +0x08
        if (flagA != 0) {
            sendReplicationData(*(uint32_t*)(this + 0x14), flagA, (void*)(this + 0xd0));
        }

        uint32_t flagB = slotBase[3];     // offset +0x0c
        if (flagB != 0) {
            // Note: This case reuses the first buffer (b0) as per original code; offset 0xd0 used again? Actually decompiled shows param +0xd0 for flagB as well.
            sendReplicationData(*(uint32_t*)(this + 0x14), flagB, (void*)(this + 0xd0));
        }

        // Advance to next slot? or final cleanup
        cleanupSentData(); // Free sent data structures
    }
};