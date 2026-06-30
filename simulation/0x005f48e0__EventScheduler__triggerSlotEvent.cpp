// FUNC_NAME: EventScheduler::triggerSlotEvent
// Address: 0x005f48e0
// This function searches for a slot by ID, checks conditions, sets a value, and triggers an event.

#include <cstdint>

// Forward declarations of external functions
void mutexLock(void* mutex);
void mutexUnlock(void* mutex);
bool isConditionMet();
void beginCriticalSection();
void endCriticalSection();
void dispatchEvent(int param1, int param2);
void updateSlotState(void* thisPtr, int param1, int param2);

// Global mutex and threshold
extern void* g_mutex; // DAT_00e2aea0
extern float g_threshold; // DAT_00e2b05c

// Structure for a slot search entry (0x5c bytes each)
struct SlotSearchEntry {
    int id;          // +0x00
    int validFlag;   // +0x04 (negative = invalid)
    // ... remaining 0x58 bytes unknown
};

// Structure for slot data (0x170 bytes each)
struct SlotData {
    uint8_t pad0[0x94];
    int value;           // +0x94
    int typeIndex;       // +0x9c (multiplied by 0x10 to index into type array)
    uint8_t pad1[0x134 - 0xA0];
    float threshold;     // +0x134
    // ... rest up to 0x170
};

// Structure for type data (16 bytes each, array at this+0x81c0)
struct TypeData {
    int field0; // +0x00 (used as first param to updateSlotState)
    int field4; // +0x04 (used as second param to updateSlotState)
    // ... remaining 8 bytes
};

int __thiscall EventScheduler::triggerSlotEvent(int this, int slotId, int newValue) {
    int index;
    SlotSearchEntry* searchEntry;
    SlotData* slot;
    TypeData* typeData;
    int typeOffset;
    int somePtr;
    char result = 0;

    // Search for slot with matching ID in the search array (10 entries, each 0x5c bytes)
    searchEntry = reinterpret_cast<SlotSearchEntry*>(this + 0x82AC);
    for (index = 0; index < 10; ++index) {
        if (searchEntry->validFlag >= 0 && searchEntry->id == slotId) {
            break;
        }
        searchEntry = reinterpret_cast<SlotSearchEntry*>(reinterpret_cast<uint8_t*>(searchEntry) + 0x5C);
    }

    if (index >= 10) {
        return 0;
    }

    // Compute pointer to the slot data (array at this+0x8210, each 0x170 bytes)
    slot = reinterpret_cast<SlotData*>(this + 0x8210 + index * 0x170);

    mutexLock(&g_mutex);

    // Get type index and look up type data
    typeOffset = slot->typeIndex * 0x10;
    typeData = reinterpret_cast<TypeData*>(this + 0x81C0 + typeOffset);
    somePtr = typeData->field4;

    if (somePtr != 0) {
        // Check global threshold and condition
        if (g_threshold <= slot->threshold && isConditionMet()) {
            slot->value = newValue;
            beginCriticalSection();
            dispatchEvent(0, newValue);
            endCriticalSection();
            result = 1;
        }
        // Notify slot state change
        updateSlotState(reinterpret_cast<void*>(this), typeData->field0, somePtr);
    }

    mutexUnlock();
    return result;
}