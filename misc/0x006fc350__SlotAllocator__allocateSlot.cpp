// FUNC_NAME: SlotAllocator::allocateSlot

class SlotAllocator {
public:
    // Offsets relative to this pointer (param_1)
    // +0x00: unknown (maybe vtable?)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: unknown
    // +0x10: Slot 0 (first dword = flags, second dword = size/priority)
    // +0x24: Slot 1
    // +0x38: Slot 2
    // +0x4C: Slot 3
    // +0x60: Slot 4
    // +0x74: Count of allocated slots (int)

    struct Slot {
        int flags;      // +0x00: Top bit indicates allocated (0x80000000) when set
        int size;       // +0x04: Size or priority
    };

    // Each slot is at offset +0x14 (20 bytes)
    static const int SLOT_SIZE = 0x14;
    static const int NUM_SLOTS = 5;

    Slot* getSlot(int index) {
        // Offsets: 0x10 + index * 0x14
        return reinterpret_cast<Slot*>(reinterpret_cast<char*>(this) + 0x10 + index * 0x14);
    }

    // Allocate a free slot with the highest size/priority
    void allocateSlot() {
        Slot* bestSlot = nullptr; // puVar1

        // Iterate over all slots
        for (int i = 0; i < NUM_SLOTS; i++) {
            Slot* current = getSlot(i);
            // Check if slot is free (top bit not set)
            if ((current->flags & 0x80000000) == 0) {
                // Compare with current best (if any)
                if (bestSlot == nullptr || bestSlot->size < current->size) {
                    bestSlot = current;
                }
            }
        }

        // If a free slot was found, mark it as allocated and decrease count
        if (bestSlot != nullptr) {
            bestSlot->flags = 0x80000000; // Mark as used
            *(int*)(reinterpret_cast<char*>(this) + 0x74) -= 1;
        }
    }
};