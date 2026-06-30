// FUNC_NAME: NetWindowManager::processSlot
// Address: 0x00705590
// Role: Process a packet window slot: handle acknowledgment, deallocate/reset slot, update connection state.

#include <cstdint>

// Forward declarations of internal engine functions (not in scope)
extern void resetSlot(int slotIndex);
extern void freePacketByOffset(int offset);
extern void freePacketPtr(void** packetPtr);
extern void updateConnection(void* connection);
extern void processNetworkLayer();
extern void processInputLayer();
extern void updateConnectionState(void* connection);
extern char isPlayerReady();
extern void notifySlotProcessed(int playerId, int slotIndex);

// Window slot structure (20 bytes each, indexed with offset = (slotIndex+1)*20)
struct WindowSlot {
    uint32_t unk0;        // +0x00
    uint32_t packet;      // +0x04 (pointer or offset, 0x48 is sentinel)
    uint32_t unk8;        // +0x08
    uint32_t sendCount;   // +0x0C
    uint32_t ackCount;    // +0x10
};

int NetWindowManager::processSlot(void* connection, int slotIndex) {
    // Compute pointer to the slot structure (skip first 20-byte header or sentinel)
    WindowSlot* slot = reinterpret_cast<WindowSlot*>(
        reinterpret_cast<char*>(this) + (slotIndex * 5 + 5) * 4
    );
    uint32_t sendCount = slot->sendCount;
    uint32_t ackCount  = slot->ackCount;
    bool flag = (*(reinterpret_cast<uint8_t*>(connection) + 0x1D4) & 1) != 0; // some per-connection flag

    if (ackCount <= sendCount) {
        if (!flag) {
            // Case: acknowledged but flag not set → reset slot
            resetSlot(slotIndex);
            return 0;
        }
        // Flag is set: deallocate packet data and clear slot
        if (slot->packet != 0) {
            int packetOffset = slot->packet - 0x48;
            if (packetOffset != 0) {
                freePacketByOffset(packetOffset);
            }
        }
        if (slot->sendCount != 0) {
            slot->sendCount--;
        }
        if (slot->packet != 0 && slot->packet != 0x48 && slot->packet != 0) {
            freePacketPtr(reinterpret_cast<void**>(&slot->packet));
            slot->packet = 0;
        }
    }

    // Common processing for all cases
    if (slot->packet == 0 || slot->packet == 0x48) {
        updateConnection(connection);
    }
    processNetworkLayer();
    processInputLayer();
    updateConnectionState(connection);

    if (slot->sendCount < slot->ackCount) {
        slot->sendCount++;
    }

    if (isPlayerReady()) {
        notifySlotProcessed(1, slotIndex);
    }
    return 1;
}