// FUNC_NAME: FrameTimeRecorder::recordTick
// Address: 0x0065ca60
// This function is called periodically (likely every frame) with the current time.
// It tracks a 30-second interval and rotates a double-buffered timestamp pair.
// When 30 seconds have elapsed since the last sample, it rotates the buffer, invokes a callback
// on the old timestamp, and records the current time to a profiler.

extern bool g_profilerInitialized; // DAT_0120588f
extern ProfilerManager g_profiler; // DAT_01203740 (some global profiler instance)

class FrameTimeRecorder {
public:
    // +0x00: vtable or something? Not used here.
    uint32_t m_lastSampleTime;      // +0x04: last time a sample was taken (30s interval)
    uint32_t m_firstTime;           // +0x08: initialization check (first time it's set)
    uint32_t m_currentTimestampLow; // +0x0C: low part of current timestamp pair
    uint32_t m_currentTimestampHigh;// +0x10: high part of current timestamp pair
    uint32_t m_previousTimestampLow; // +0x14: low part of previous timestamp pair (after swap)
    uint32_t m_previousTimestampHigh;// +0x18: high part of previous timestamp pair (after swap)
    uint32_t m_prevPrevTimestampLow; // +0x1C: low part of older timestamp pair
    uint32_t m_prevPrevTimestampHigh;// +0x20: high part of older timestamp pair

    void __thiscall recordTick(uint32_t currentTime) {
        // First call initialization: store the starting time
        if (m_firstTime == 0) {
            m_firstTime = currentTime;
        }

        // If at least 30 seconds have passed since the last sample
        if ((currentTime - m_lastSampleTime) > 30000) {
            m_lastSampleTime = currentTime;

            // Rotate the timestamp buffer:
            // Save the oldest high value (will be passed to callback)
            uint32_t oldHigh = m_prevPrevTimestampHigh;

            // Shift values: move previous pair -> oldest, current -> previous
            m_prevPrevTimestampHigh = m_prevPrevTimestampLow;
            m_previousTimestampLow  = m_currentTimestampLow;
            m_prevPrevTimestampLow  = oldHigh;
            m_previousTimestampHigh = m_currentTimestampHigh;

            // Call the processing function with the old timestamp high value
            FUN_0065c810(oldHigh);

            // Initialize the global profiler on first call
            if (!g_profilerInitialized) {
                g_profilerInitialized = true;
                FUN_00662100(&g_profiler);
                FUN_006622a0(&g_profiler);
            }

            // Push the current timestamp pair (8 bytes) to the profiler
            FUN_00662350(&m_currentTimestampLow, 8, &g_profiler);
        }
    }
};