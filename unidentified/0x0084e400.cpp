// 0x0084e400: EventLog::pushEvent - push an event into the circular event log buffer

extern int g_timestamp; // DAT_01205224 - global tick counter

struct EventLog {
    int* buffer;      // +0x00: base pointer to array of 8-byte entries
    int capacity;     // +0x04: maximum number of entries in the buffer
    int writeIndex;   // +0x08: current insertion index (decrements, wraps)
    int count;        // +0x0C: number of entries (capped at capacity)
};

void __thiscall EventLog::pushEvent(int eventType)
{
    // Adjust count to ensure it stays within [0, capacity]
    if (this->count >= this->capacity && this->count != 0) {
        this->count--; // keep count at capacity (don't exceed)
    }
    this->count++; // new entry always increases count

    // Write index moves backwards (LIFO-like insertion)
    this->writeIndex--;
    if (this->writeIndex < 0) {
        this->writeIndex = this->capacity - 1; // wrap to end of buffer
    }

    // Store the event data (type and timestamp) at the new index
    int* entry = &this->buffer[this->writeIndex * 2]; // each entry = 2 ints
    entry[0] = eventType;    // event identifier
    entry[1] = g_timestamp;  // capture current time
}