// FUNC_NAME: findAvailableSlot
// Function address: 0x005a1e70
// Searches a table of entries (size 0x20 each) for the first entry where the state field at offset +0x1c is not equal to 3.
// Returns a value with low byte 0 on success (found), low byte 1 on failure (not found).
// The high 24 bits encode the address of the found entry (or the end address if not found).

// Global structure for the slot manager (likely part of networking or input system)
struct SlotManager {
    uint32_t count;          // +0x00: number of slots
    uint32_t unknown;        // +0x04
    uint32_t baseAddress;    // +0x08: pointer to array of SlotEntry (each 0x20 bytes)
};

// Each slot entry (size 0x20)
struct SlotEntry {
    uint8_t data[0x1c];      // +0x00 to +0x1b: unknown fields
    uint32_t state;          // +0x1c: state (3 = occupied/active, other = free)
};

extern SlotManager gSlotManager; // DAT_0119cae4

uint32_t findAvailableSlot(void)
{
    uint32_t base = gSlotManager.baseAddress;
    uint32_t count = gSlotManager.count;
    uint32_t end = base + count * 0x20;

    // Iterate over all slots
    for (uint32_t ptr = base; ptr < end; ptr += 0x20) {
        SlotEntry* entry = (SlotEntry*)ptr;
        if (entry->state != 3) {
            // Found a slot not in state 3; return its address with low byte cleared (success)
            return ptr & 0xFFFFFF00;
        }
    }

    // No free slot found; return end address with low byte set to 1 (failure)
    return (end & 0xFFFFFF00) | 1;
}