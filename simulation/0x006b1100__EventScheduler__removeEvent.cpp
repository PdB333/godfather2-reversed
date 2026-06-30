// FUNC_NAME: EventScheduler::removeEvent

// Event structure (fields used by this function)
struct Event {
    uint32_t key;       // +0x38 – key used for binary search
    // ... other fields ...
    uint32_t slotIndex; // +0xc4 – index into small usage counter array (<10)
};

// Class EventScheduler – manages a sorted array of events (8-byte entries: key + value)
// Offsets:
//   this+0x34: pointer to array of Entry (8 bytes each)
//   this+0x38: count of entries (uint32)
//   this+0x40: array of 10 usage counters (int32, one per slot)

void __thiscall EventScheduler::removeEvent(Event* event) {
    // Decrement the usage counter for the event's slot, if slot is valid
    if (event->slotIndex < 10) {
        m_slotUsageCounts[event->slotIndex]--;   // m_slotUsageCounts at this+0x40
    }

    uint32_t count = m_entryCount;  // this+0x38
    if (count == 0) {
        return;
    }

    // Binary search for an entry whose key matches event->key
    int32_t low = 0;
    int32_t high = count - 1;
    while (low <= high) {
        int32_t mid = (low + high) >> 1;
        uint32_t midKey = m_entries[mid].key;   // m_entries at this+0x34, offset 0 is key
        if (midKey < event->key) {
            low = mid + 1;
        } else if (midKey > event->key) {
            high = mid - 1;
        } else {
            // Found the entry to remove; shift all later entries left by one slot
            if (mid < static_cast<int32_t>(count) - 1) {
                for (int32_t i = mid; i < static_cast<int32_t>(count) - 1; i++) {
                    m_entries[i] = m_entries[i + 1];
                }
            }
            m_entryCount--;
            return;
        }
    }
    // Key not found – nothing removed
}