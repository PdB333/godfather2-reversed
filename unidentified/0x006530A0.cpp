// 0x006530A0 - TNL ghost replication update / pending packet queue builder
//
// Observed behavior:
// - Serializes the current replication window via FUN_00653230.
// - When updateMode == 0, allocates and links a new pending update node into a
//   FIFO list and stamps it with the current transport sequence anchor.
// - Stages the packet writer state, patches the active ghost/object id, and
//   commits the packet through a virtual method.
// - If a lower-level replication channel is active, forwards the current
//   sequence window into FUN_0065a6c0 and finalizes it with FUN_0064c980.
//
// This reconstruction keeps the original thiscall-style member function shape,
// but only the offsets touched by the function are modeled explicitly.

#include <cstddef>
#include <cstdint>

struct PendingUpdateNode {
    std::uint8_t pad_00[0x04];
    std::uint32_t sourceStamp;   // +0x04: copied from transport object + 100 bytes
    std::uint8_t pad_08[0x08];
    PendingUpdateNode* next;     // +0x10: singly-linked pending list
};

class TnlGhostReplicationController {
public:
    void __thiscall buildAndQueueGhostUpdate(int updateMode);
};

template <typename T>
static inline T& field(void* base, std::size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(base) + offset);
}

extern void FUN_00653230(TnlGhostReplicationController* self, int updateMode);
extern void* FUN_00653760();
extern void FUN_0065a6c0(void* replicationChannel, int windowHigh, int windowLow, int updateMode);
extern void FUN_0064c980(int flushType, void* replicationChannel);

void __thiscall TnlGhostReplicationController::buildAndQueueGhostUpdate(int updateMode) {
    FUN_00653230(this, updateMode);

    // Mode 0 is the "open a fresh record" path.
    // The game uses this when it wants a new pending snapshot node rather than
    // only updating the already-open replication state.
    if (updateMode == 0) {
        using CreatePendingNodeFn = PendingUpdateNode* (__thiscall *)(TnlGhostReplicationController*);
        auto createPendingNode = reinterpret_cast<CreatePendingNodeFn>(
            (*reinterpret_cast<void***>(this))[0x4C / sizeof(void*)]
        );
        PendingUpdateNode* node = createPendingNode(this);

        PendingUpdateNode*& pendingHead = field<PendingUpdateNode*>(this, 0x11C);
        PendingUpdateNode*& pendingTail = field<PendingUpdateNode*>(this, 0x120);

        if (pendingHead == nullptr) {
            pendingHead = node;
        } else {
            pendingTail->next = node;
        }
        pendingTail = node;

        // Clear the new tail and stamp it with the current transport-side anchor.
        // Ghidra shows the source read coming from the owner object at +0x1A4,
        // then a 100-byte offset into that object.
        node->next = nullptr;
        void* transportContext = field<void*>(this, 0x1A4);
        node->sourceStamp = *reinterpret_cast<std::uint32_t*>(
            reinterpret_cast<std::uint8_t*>(transportContext) + 100
        );

        // FUN_00653760 uses the current register state to flush a pending control
        // byte / header sequence into the bitstream. The returned object is then
        // patched with the active ghost/object identifier from +0x1C8.
        void* packetWriter = FUN_00653760();
        field<std::uint32_t>(packetWriter, 0x34) = field<std::uint32_t>(this, 0x1C8);

        // Virtual slot +0x38 commits the packet after the header patch above.
        using CommitPendingPacketFn = void (__thiscall *)(TnlGhostReplicationController*);
        auto commitPendingPacket = reinterpret_cast<CommitPendingPacketFn>(
            (*reinterpret_cast<void***>(this))[0x38 / sizeof(void*)]
        );
        commitPendingPacket(this);
    }

    // If a replication channel exists, mirror the current sequence window into it.
    // The two integer arguments come from the controller's window state:
    //   - +0x98: upper/last acknowledged position
    //   - +0x90: lower/current position
    // The third argument is the mode flag passed into this function.
    void* replicationChannel = field<void*>(this, 0x1B0);
    if (replicationChannel != nullptr) {
        FUN_0065a6c0(replicationChannel,
                     field<std::uint32_t>(this, 0x98),
                     field<std::uint32_t>(this, 0x90),
                     updateMode);
        FUN_0064c980(3, replicationChannel);
    }
}
