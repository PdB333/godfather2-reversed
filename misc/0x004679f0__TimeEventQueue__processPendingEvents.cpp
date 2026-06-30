// FUNC_NAME: TimeEventQueue::processPendingEvents

// Function address: 0x004679f0
// Processes a queue of time events (tags 3=update, 4=validate) for this object.
// The queue stores pairs (int tag, float index) at 8 bytes each.
// The index (float) is rounded to an integer to index into a global array of 0x54-byte structures.
// If the structure's owner equals this, it updates accumulated time and last timestamp.

#include <cstdint>

// Forward declarations for external functions
extern int validateEvent(void* thisPtr);           // FUN_00636850
extern void setObjectState(int* obj, int state);   // FUN_006259b0
extern int getCurrentTime();                       // FUN_00b9a1c0 (e.g., GetTickCount)

// Global data (from DAT_0122346c)
extern int g_timeEntryArrayBase;  // base address for 0x80 entries of size 0x54

// Structure for a time entry in the global array (size 0x54)
struct TimeEntry {
    int owner;               // +0x00: owner object pointer (this)
    int accumulatedTime;     // +0x04: accumulated time in ms
    int lastTimestamp;       // +0x08: last update timestamp
    // ... other fields (38*0x54 - 12 = 72 bytes) ...
};

// Event queue element (8 bytes)
struct QueueElement {
    int tag;          // +0x00: event type (3=update, 4=validate)
    float index;      // +0x04: index into TimeEntry array
};

class TimeEventQueue {
public:
    // Assumed offsets:
    // +0x00: vtable? (not used here)
    // +0x08: QueueElement* beginPtr (start of queue)
    // +0x0C: QueueElement* currentPtr (position to process)
    // The queue is presumably a circular buffer or linear.

    int processPendingEvents() {
        QueueElement* elem = reinterpret_cast<QueueElement*>(*reinterpret_cast<int*>(this + 0x0C));
        QueueElement* end = reinterpret_cast<QueueElement*>(*reinterpret_cast<int*>(this + 0x08));
        int accumulatedTime = 0;

        // If current pointer is valid and less than end (or buffer wraps)
        if (elem >= end || elem == nullptr) {
            goto write_event;
        }

        // Check tag
        if (elem->tag != 3) {
            if (elem->tag != 4) {
                goto write_event; // unknown tag, skip
            }
            // Tag 4: validate event
            if (validateEvent(this) == 0) {
                goto write_event;
            }
        }

        // Read the index float from the current element
        QueueElement* curElem = reinterpret_cast<QueueElement*>(*reinterpret_cast<int*>(this + 0x0C));
        if (curElem < end && curElem != nullptr) {
            if (curElem->tag != 3) {
                if (curElem->tag == 4) {
                    if (validateEvent(this) != 0) {
                        // Validated, use this element
                        accumulatedTime = static_cast<int>(curElem->index); // float to int
                    }
                }
                // else: tag not 3 or 4, will go to else branch
            } else {
                // Tag 3: use the index directly
                accumulatedTime = static_cast<int>(curElem->index);
            }
        }

        // Now accumulatedTime is an integer index into the TimeEntry array
        int timeEntryIndex = accumulatedTime;
        if (timeEntryIndex >= 0 && timeEntryIndex < 0x80) {
            TimeEntry* entry = reinterpret_cast<TimeEntry*>(g_timeEntryArrayBase + 0x14 + timeEntryIndex * 0x54);
            if (entry->owner == reinterpret_cast<int>(this)) {
                // Update this object's time entry
                setObjectState(reinterpret_cast<int*>(this), 2); // state 2 (running?)
                int newTimestamp = getCurrentTime();
                int oldTimestamp = entry->lastTimestamp;
                entry->lastTimestamp = newTimestamp;
                entry->accumulatedTime += (newTimestamp - oldTimestamp);
                accumulatedTime = entry->accumulatedTime;
            }
        }

    write_event:
        // Write a new event (tag 3) with the accumulated time as float
        QueueElement* writePos = reinterpret_cast<QueueElement*>(*reinterpret_cast<int*>(this + 0x08));
        if (writePos != nullptr) {
            writePos->tag = 3;
            writePos->index = static_cast<float>(accumulatedTime);
            // Advance write pointer by 8 bytes
            *reinterpret_cast<int*>(this + 0x08) = reinterpret_cast<int>(writePos) + 8;
        }
        return 1; // success
    }

    // Pad to make the class layout consistent (if needed)
    // This is just a reconstructed function, actual class layout may differ.
};