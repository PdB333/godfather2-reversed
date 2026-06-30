//FUNC_NAME: EventScheduler::setEventTime
// Function address: 0x005f8dc0
// Role: Sets the time for a specific event identified by m_targetId, then reorders the heap.

struct EventEntry {
    int id;      // +0x00
    float time;  // +0x04
};

class EventScheduler {
public:
    int m_eventCount;   // +0x00
    int m_pad;          // +0x04 (unused)
    EventEntry* m_events; // +0x08
    int m_targetId;     // stored in unaff_EDI, used as search key

    void setEventTime(float newTime);
private:
    void siftUp();   // FUN_005f8b00 – bubble up after decreasing time
    void siftDown(); // FUN_005f8b50 – bubble down after increasing time
};

void EventScheduler::setEventTime(float newTime) {
    int count = this->m_eventCount;
    if (count != 0 && this->m_targetId != 0) {
        int index = 1; // 1-based indexing; entry 0 is a dummy sentinel
        if (count > 0) {
            EventEntry* entry = this->m_events;
            do {
                entry++; // advance to next entry (skip dummy)
                if (entry->id == this->m_targetId) {
                    break;
                }
                index++;
            } while (index <= count);
        }
        float oldTime = entry->time;
        entry->time = newTime;
        if (newTime < oldTime) {
            this->siftUp();
        } else if (oldTime < newTime) {
            this->siftDown();
        }
    }
}