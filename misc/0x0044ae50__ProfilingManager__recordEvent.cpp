// FUNC_NAME: ProfilingManager::recordEvent
// Function at 0x0044ae50
// Records an event with a timestamp into a circular buffer. If the buffer is full, processes the oldest event first.
// When profiling is disabled, processes the event immediately without buffering.
class ProfilingManager {
public:
    struct EventEntry {
        uint32_t eventId;     // +0x00
        uint32_t elapsedMs;   // +0x04 (delta from previous event)
    };

    char m_bEnabled;          // +0x14
    uint32_t m_bufferSize;    // +0x1c (max entries)
    uint32_t m_readIndex;     // +0x20 (index of oldest unprocessed event)
    uint32_t m_count;         // +0x24 (number of events in buffer)
    EventEntry* m_pBuffer;    // +0x18 (pointer to ring buffer)
    uint64_t m_lastTimestamp; // +0x08 (low part) +0x0c (high part) PerformanceCounter value at last event

    void recordEvent(uint32_t eventId) {
        if (!m_bEnabled) {
            processSample(eventId);
            return;
        }

        // If buffer is full, pop the oldest event and process it
        if (m_bufferSize <= m_count) {
            EventEntry* entry = &m_pBuffer[m_readIndex];
            uint32_t oldEventId = entry->eventId;
            m_readIndex = (m_readIndex + 1) % m_bufferSize;
            m_count--;
            processSample(oldEventId);
        }

        // Record new event with elapsed time since last event
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        uint64_t elapsed = (currentTime.QuadPart - m_lastTimestamp) * 1000;
        uint32_t elapsedMs = (uint32_t)(elapsed / g_highPerformanceFrequency);

        uint32_t writePos = (m_readIndex + m_count) % m_bufferSize;
        m_pBuffer[writePos].eventId = eventId;
        m_pBuffer[writePos].elapsedMs = elapsedMs;
        m_count++;

        m_lastTimestamp = currentTime.QuadPart;
    }

private:
    // Processes a recorded event (e.g., outputs to log)
    void processSample(uint32_t eventId); // calls FUN_0044a0e0
};

// External: high‑performance timer frequency (units per second)
extern uint64_t g_highPerformanceFrequency; // DAT_01163ec0/4