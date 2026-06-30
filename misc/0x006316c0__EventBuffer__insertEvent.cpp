// FUNC_NAME: EventBuffer::insertEvent
// Function address: 0x006316c0
// This function inserts an 8-byte event (type + float value) into a buffer.
// It checks existing events at the buffer start and start+8 to determine the type,
// then writes a random value. The buffer is managed via m_writePtr and m_bufferStart.

#include <cstdlib> // for rand, but we use custom random

// Forward declarations of called functions
bool getFloatValue(float* out); // FUN_00636850
void debugPrint(const char* msg); // FUN_00627ac0
float getRandomFloat(); // FUN_00b9dbba

// Global constant (likely 0.0f or some sentinel)
extern const float g_sentinelFloat; // DAT_00e2b05c

// Structure for an 8-byte event entry
struct EventEntry {
    int type;   // +0x00
    float value; // +0x04
};

// Structure for the event buffer manager
struct EventBuffer {
    EventEntry* m_writePtr;   // +0x08: current write position
    EventEntry* m_bufferStart; // +0x0c: pointer to the beginning of the buffer
};

int EventBuffer::insertEvent() {
    EventEntry* entry;
    int desiredType = 3; // initial desired type
    float tempValue;
    int tempType;
    float local_c;
    float local_18;
    float local_14;

    // Check the entry at bufferStart+1 (second entry)
    entry = m_bufferStart + 1; // +8 bytes from start
    if (m_writePtr <= entry) goto skip_first;
    if (entry == nullptr) goto skip_first;
    if (entry->type != 3) {
        if (entry->type != 4) goto skip_first;
        if (!getFloatValue(&local_14)) goto skip_first;
        tempType = 3;
        local_c = local_14;
        entry = reinterpret_cast<EventEntry*>(&tempType); // fake entry
    }
    local_14 = entry->value;
    if (local_14 == g_sentinelFloat) {
        do {
            entry = m_bufferStart + 1;
            if ((entry < m_writePtr) && (entry != nullptr)) {
                if (entry->type == desiredType) break;
                if (entry->type == 4) {
                    if (getFloatValue(&local_18)) break;
                }
            }
            desiredType = 2;
            debugPrint("number");
skip_first:
            local_14 = 0.0f;
        } while (true);
    }

    // Check the entry at bufferStart (first entry)
    entry = m_bufferStart;
    if (m_writePtr <= entry) goto skip_second;
    if (entry == nullptr) goto skip_second;
    if (entry->type != desiredType) {
        if (entry->type != 4) goto skip_second;
        if (!getFloatValue(&local_18)) goto skip_second;
        local_c = local_18;
        entry = reinterpret_cast<EventEntry*>(&tempType);
        tempType = desiredType;
    }
    local_18 = entry->value;
    if (local_18 == g_sentinelFloat) {
        do {
            entry = m_bufferStart;
            if ((entry < m_writePtr) && (entry != nullptr)) {
                if (entry->type == desiredType) break;
                if (entry->type == 4) {
                    if (getFloatValue(&tempType)) break;
                }
            }
            desiredType = 1;
            debugPrint("number");
skip_second:
            local_18 = 0.0f;
        } while (true);
    }

    // Write the new event at the current write position
    m_writePtr->type = desiredType;
    m_writePtr->value = getRandomFloat();
    m_writePtr++; // advance write pointer by 8 bytes (sizeof(EventEntry))

    return 1;
}