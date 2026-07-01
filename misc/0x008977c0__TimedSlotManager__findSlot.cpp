// FUNC_NAME: TimedSlotManager::findSlot
// Address: 0x008977c0
// Searches a sorted array of slots for one matching (g_tickCount % m_windowSize).
// Returns pointer to matching slot (if valid) or pointer to first slot with key > remainder (insertion point).
// If no slots exist, returns the quotient of g_tickCount / m_windowSize as a fallback.
// Slot entries are 16 bytes: +0x0 unknown, +0x4 unknown, +0x8 flags (bit1 = active), +0xC key (0..windowSize-1)

#include <cstdint>

// Forward declaration (defined elsewhere)
uint32_t FUN_00897520(uint32_t index, void* entryPtr, uint8_t hash[12]);

struct SlotEntry {
    int32_t field_0;      // +0x00
    int32_t field_4;      // +0x04
    uint32_t flags;       // +0x08  (bit1 = 0x2 = active)
    uint32_t key;         // +0x0C  (remainder value)
};

struct TimedSlotManager {
    int32_t m_ownerId;                // +0x00
    SlotEntry* m_slots;               // +0x04  (array of m_numSlots entries)
    int32_t field_8;                  // +0x08
    int32_t m_numSlots;               // +0x0C  (number of used slots)
    int32_t field_10;                 // +0x10
    int32_t m_windowSize;             // +0x14  (divisor)
    int32_t field_18;                 // +0x18
    void (*m_computeHash)(int32_t, uint8_t[12]); // +0x1C (hash function)
};

extern uint32_t g_tickCount; // DAT_01205220

__thiscall uint32_t TimedSlotManager::findSlot(void) {
    uint8_t hashOutput[12];
    uint32_t quotient;
    uint32_t remainder;
    int32_t index;
    uint32_t i;

    // Compute hash from owner ID (probably for collision/slot identity)
    m_computeHash(m_ownerId, hashOutput);

    // Determine search key from global tick count
    quotient = g_tickCount / m_windowSize;
    remainder = g_tickCount % m_windowSize;

    if (m_numSlots != 0) {
        for (i = 0, index = 0; i < (uint32_t)m_numSlots; i++, index += sizeof(SlotEntry)) {
            uint32_t currKey = *(uint32_t*)((uint8_t*)m_slots + offsetof(SlotEntry, key) + index);
            SlotEntry* entry = (SlotEntry*)((uint8_t*)m_slots + index);

            if (currKey == remainder) {
                // Check if slot is active (bit1 of flags)
                if (entry->flags & 0x2) {
                    // Process active slot (e.g., handle timeout or collision)
                    return FUN_00897520(i, entry, hashOutput);
                }
            }
            else if (remainder < currKey) {
                // Insertion point: first slot with key > remainder
                return (uint32_t)entry;
            }
        }
        // If all keys < remainder, return pointer to last slot
        return (uint32_t)((SlotEntry*)((uint8_t*)m_slots + (m_numSlots - 1) * sizeof(SlotEntry)));
    }

    // No slots – fallback to quotient (possibly used as initial pointer)
    return quotient;
}