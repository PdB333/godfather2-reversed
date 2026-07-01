// FUNC_NAME: TimedActionManager::tickSlot
#include <cstdint>

// Global current time (in ticks/ms).  Source: DAT_01205224
extern uint32_t g_currentTime;

// Structure for per-slot timing parameters (3 ints, 12 bytes)
struct SlotTimingParams {
    int32_t m_threshold;  // +0x00: number of hits to trigger
    int32_t m_unused;     // +0x04: (unused in this function)
    int32_t m_delay;      // +0x08: reset delay after trigger
};

// Structure for per-slot timer state (8 bytes)
struct SlotTimerState {
    uint32_t m_timeStamp; // +0x00: next expiration time
    int32_t  m_count;     // +0x04: current count
};

class TimedActionManager {
public:
    // Update the timer for a single slot.
    // Called each frame to advance counters and handle threshold triggers.
    void __thiscall tickSlot(int slotIndex) {
        uint32_t currentTime = g_currentTime;

        // Timing parameters for this slot (array at this+24, stride 12)
        SlotTimingParams* params = reinterpret_cast<SlotTimingParams*>(
            reinterpret_cast<uint8_t*>(this) + (slotIndex * 3 + 6) * 4
        );

        // Timer state for this slot (array at this+0x354, stride 8)
        SlotTimerState* timer = reinterpret_cast<SlotTimerState*>(
            reinterpret_cast<uint8_t*>(this) + 0x354 + slotIndex * 8
        );

        // If the timer has expired (timestamp <= current time)
        if (timer->m_timeStamp <= currentTime) {
            timer->m_count++;
        }

        // If count reached the threshold, reset timer with delay
        if (timer->m_count == params->m_threshold) {
            timer->m_timeStamp = currentTime + params->m_delay;
            timer->m_count = 0;
        }
    }
};