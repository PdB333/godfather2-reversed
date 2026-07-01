// FUNC_NAME: StreamManager::handleStopEvent
// Function address: 0x008cf4e0
// Decompiled reconstruction for The Godfather 2 (EA EARS engine)
// This handler processes a stop-stream event (event ID = 0x20e5862).
// It waits for a condition variable and, if the stream state changed,
// calls the engine's stop-all-streams routine.

#include <cstdint>

// Event ID for stop stream (likely a hash)
const uint32_t kEventStopStream = 0x20e5862;

// Forward declarations for engine functions
// FUN_008cf410: returns the global stream manager instance
void* getStreamManager();  
// FUN_004df8b0: stops all active streams on the given manager
void stopAllStreams(void* manager);  
// FUN_004a3d60: waits on a condition variable; takes a 12-byte timeout buffer,
// a pointer to the variable to watch, and a mutex/lock.
void waitForCondition(void* timeout, int* conditionVar, int mutex);

class StreamManager {
public:
    // Field offsets (based on decompiled code):
    // +0x20: uint32_t m_activeFlag; // non-zero if streaming currently active
    // +0x28: int m_mutex;          // mutex or lock used with condition wait
    // +0x2c: int m_streamState;    // state variable that changes on signal

    void __thiscall handleStopEvent(uint32_t eventType, void* eventData);
};

void __thiscall StreamManager::handleStopEvent(uint32_t eventType, void* eventData) {
    // Check for correct event ID and non-null data
    if (eventType != kEventStopStream || eventData == nullptr)
        return;

    // Save current stream state before potential wait
    int oldState = m_streamState;

    // Wait for condition to be signalled (timeout buffer left uninitialized as in original)
    uint8_t timeoutBuffer[12]; // uninitialized – may be filled by waitForCondition
    waitForCondition(timeoutBuffer, &m_streamState, m_mutex);

    // If state changed and streaming is still active, stop all streams
    if (oldState != m_streamState && m_activeFlag != 0) {
        void* manager = getStreamManager();
        stopAllStreams(manager);
    }
}