// FUNC_NAME: PendingActionManager::addPendingFlags
// Address: 0x004816c0
// Role: Adds pending flags to a target object and enqueues it in a globally linked list if not already pending.
// The object at this+0x0C is the target; its fields:
//   +0x10 nextPending (pointer)
//   +0x0C prevPending (pointer)
//   +0x14 pendingFlags (uint32)
//   +0x30 someFlags (uint32, bit 1 tested)
//   +0x3C someByte (byte, bit 0 tested)
// Global s_pendingHead at 0x01205a28 is the head of the pending list.

#include <cstdint>

class PendingActionManager {
public:
    // Adds the given flags to the pending flags of the target object.
    // If the object was not already pending (pendingFlags == 0) and the global list is non-empty,
    // it inserts the object at the front of the list.
    // The object is only enqueued if it passes state checks (bit 1 of someFlags clear, bit 0 of someByte clear).
    void addPendingFlags(uint32_t flags) {
        // Retrieve the target object pointer at offset 0x0C.
        PendingTarget* target = *reinterpret_cast<PendingTarget**>(reinterpret_cast<char*>(this) + 0x0C);
        if (target == nullptr)
            return;

        // Check if the object is eligible: bit 1 of someFlags must be clear, bit 0 of someByte must be clear.
        if (((target->someFlags >> 1) & 1) != 0)
            return;
        if ((target->someByte & 1) != 0)
            return;
        if (flags == 0)
            return;

        // Global head of pending list.
        PendingTarget* oldHead = s_pendingHead;

        // If the object is not already pending (pendingFlags == 0), insert it into the list.
        if (target->pendingFlags == 0) {
            // The comma operator in the original code: set newHead = target, then check if oldHead != 0.
            // If oldHead != 0, link the object at the front.
            if (oldHead != nullptr) {
                target->nextPending = oldHead;
                oldHead->prevPending = target;
            }
            // Update head to target (whether or not oldHead existed).
            s_pendingHead = target;
        } else {
            // If already pending, keep the head unchanged.
            s_pendingHead = oldHead;
        }

        // Add the new flags to the pending flags.
        target->pendingFlags |= flags;
    }

private:
    // Target structure (inferred offsets)
    struct PendingTarget {
        uint32_t someFlags;        // +0x30 (bit 1 used)
        uint8_t  someByte;         // +0x3C (bit 0 used)
        PendingTarget* prevPending; // +0x0C
        PendingTarget* nextPending; // +0x10
        uint32_t pendingFlags;     // +0x14
    };

    static PendingTarget* s_pendingHead; // global at 0x01205a28
};