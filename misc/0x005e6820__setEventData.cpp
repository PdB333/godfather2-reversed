// FUNC_NAME: setEventData
// Address: 0x005e6820
// Role: Updates two 32-bit data fields in an event entry identified by a 16-bit event ID.
// Returns true on success, false if ID out of range or entry not found.

#include <cstdint>

// Global base pointer for event array (DAT_012234bc)
extern uint8_t* g_eventArrayBase;

// Event entry structure (size 0x30 bytes)
struct EventEntry {
    // +0x00: unknown (8 bytes? Actually 0x30 total)
    // +0x24: data0 (param2)
    // +0x28: data1 (param3)
    // +0x2C: eventId
    uint32_t data0;   // +0x24
    uint32_t data1;   // +0x28
    uint32_t eventId; // +0x2C
};

// Maximum number of event slots (0x200 = 512)
static const uint32_t kMaxEventSlots = 0x200;

// Size of each entry in bytes
static const uint32_t kEntrySize = 0x30;

bool setEventData(uint32_t eventId, uint32_t data0, uint32_t data1)
{
    uint16_t index = static_cast<uint16_t>(eventId & 0xFFFF);
    if (index >= kMaxEventSlots) {
        return false;
    }

    // Calculate pointer to the event entry (base + 0x10 + index * 0x30)
    EventEntry* entry = reinterpret_cast<EventEntry*>(
        g_eventArrayBase + 0x10 + index * kEntrySize
    );

    // Validate pointer and event ID match
    if (entry == nullptr || entry->eventId != eventId) {
        return false;
    }

    // Update the two data fields
    entry->data0 = data0;
    entry->data1 = data1;

    return true;
}