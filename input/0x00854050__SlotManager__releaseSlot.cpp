// FUNC_NAME: SlotManager::releaseSlot
// Address: 0x00854050
// Role: Releases a slot in a fixed-size circular slot manager (15 slots).
// The manager tracks used slots with a head index and count.
// After releasing, if the released slot was the head, it advances head to the next used slot.

struct SlotManager {
    uint head;          // +0x00: Index of the oldest used slot (mod 15)
    uint unknown;       // +0x04: Possibly capacity or tail (unused here)
    uint count;         // +0x08: Number of used slots
    uint slots[15];     // +0x0C: Slot usage flags (0 = free, non-zero = used)
};

void __thiscall SlotManager::releaseSlot(uint slotIndex) {
    if (slotIndex < 15 && slots[slotIndex] != 0) {
        // Debug/log call (likely a no-op in release builds)
        FUN_007075e0(0);

        slots[slotIndex] = 0;
        count--;

        // If the released slot was the head, advance head to next used slot
        if (slotIndex == head) {
            uint newHead = head;
            while (newHead < head + 15) {
                if (slots[newHead % 15] != 0) {
                    head = newHead % 15;
                    return;
                }
                newHead++;
            }
            // If no used slot found, head remains unchanged (but count is 0)
        }
    }
}