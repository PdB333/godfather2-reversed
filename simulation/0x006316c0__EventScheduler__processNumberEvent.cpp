// FUNC_NAME: EventScheduler::processNumberEvent
// Address: 0x006316c0
// This function appears to manage a buffer of event entries (type + timestamp) and writes a "number" event.
// It checks for existing entries at specific slots and adjusts the event type accordingly.

#include <cstdint>

// Represents an 8-byte event entry: type (int) and value (int, often a timestamp).
struct EventEntry {
    int32_t type;   // +0x0
    int32_t value;  // +0x4
};

// Global constant (float interpreted as int?) – likely a sentinel timestamp.
extern const float g_numberEventValue; // DAT_00e2b05c

// Forward declarations for external functions
int32_t convertEventOrValidate(EventEntry* entry); // FUN_00636850
void debugLogNumber(); // FUN_00627ac0 (prints "number")
int32_t getCurrentTime(); // FUN_00b9dbba (returns time in some unit)

class EventScheduler {
public:
    // Offsets relative to this:
    // +0x08: writePtr (EventEntry*)
    // +0x0C: readPtr (EventEntry*) – points to base of event buffer (array of entries)

    EventEntry* m_writePtr;  // +0x8: next write position
    EventEntry* m_readPtr;   // +0xC: base of event buffer (actual pointer)

    int32_t processNumberEvent();
};

int32_t EventScheduler::processNumberEvent() {
    EventEntry* pEntry = nullptr;
    int32_t result = 0;
    int32_t desiredType = 3; // Start with type 3

    // Initially examine the second event in the buffer (index 1).
    // m_readPtr points to the first entry; adding 8 bytes moves to the second entry.
    pEntry = (EventEntry*)((uintptr_t)m_readPtr + 8);

    // If write pointer is <= second entry or it's null, skip to cleanup.
    if (m_writePtr <= pEntry || pEntry == nullptr) {
        goto cleanup; // LAB_00631780
    }

    // Check type of the second entry.
    if (pEntry->type != 3) {
        if (pEntry->type != 4) {
            goto cleanup; // Unknown type, skip
        }
        // Type 4: attempt to convert/validate
        result = convertEventOrValidate(pEntry);
        if (result == 0) {
            goto cleanup;
        }
        // If conversion succeeds, set desiredType to 3 and temporarily use local
        desiredType = 3;
        // piVar1 = &local_10, but we can emulate by using a local variable
        EventEntry localEntry;
        localEntry.type = 3;
        localEntry.value = pEntry->value; // use the value from the second entry
        pEntry = &localEntry;
    }

    // Now pEntry points to an entry of type 3 (or converted from type 4)
    float entryValue = (float)pEntry->value; // interpret as float

    // If the value equals our sentinel, search for a better matching entry.
    if (entryValue == g_numberEventValue) {
        do {
            // Reload the second entry pointer from m_readPtr
            pEntry = (EventEntry*)((uintptr_t)m_readPtr + 8);
            if (m_writePtr <= pEntry || pEntry == nullptr) {
                // No valid entry; set local value to 0 and continue searching
                goto resetLocalValue1;
            }
            if (pEntry->type == desiredType) {
                break; // Found matching type
            }
            if (pEntry->type == 4) {
                result = convertEventOrValidate(pEntry);
                if (result != 0) {
                    break; // Successful conversion
                }
            }
            // No match, decrement desired type and log
            desiredType = 2;
            debugLogNumber();

        resetLocalValue1:
            entryValue = 0.0f; // local_14 = 0.0
        } while (true);
    }

    // Now examine the first entry in the buffer (index 0).
    pEntry = m_readPtr; // Base of buffer

    if (m_writePtr <= pEntry || pEntry == nullptr) {
        goto cleanup2; // LAB_00631831
    }

    if (pEntry->type != desiredType) {
        if (pEntry->type != 4) {
            goto cleanup2;
        }
        result = convertEventOrValidate(pEntry);
        if (result == 0) {
            goto cleanup2;
        }
        // Use a local entry with desiredType and the converted value
        EventEntry localEntry2;
        localEntry2.type = desiredType;
        localEntry2.value = pEntry->value;
        pEntry = &localEntry2;
    }

    float firstValue = (float)pEntry->value;

    if (firstValue == g_numberEventValue) {
        do {
            pEntry = m_readPtr; // First entry again
            if (m_writePtr <= pEntry || pEntry == nullptr) {
                goto resetLocalValue2;
            }
            if (pEntry->type == desiredType) {
                break;
            }
            if (pEntry->type == 4) {
                result = convertEventOrValidate(pEntry);
                if (result != 0) {
                    break;
                }
            }
            // Decrement desired type further and log
            desiredType = 1;
            debugLogNumber();

        resetLocalValue2:
            firstValue = 0.0f; // local_18 = 0.0
        } while (true);
    }

    // Write the final event at the write pointer.
    m_writePtr->type = desiredType;
    m_writePtr->value = (int32_t)(float)getCurrentTime(); // timestamp
    m_writePtr++; // Advance write pointer by sizeof(EventEntry) = 8 bytes

    return 1;
}