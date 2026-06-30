// FUNC_NAME: ProfilerState::getInstance
// Address: 0x004d94d0
// Role: Returns pointer to a singleton ProfilerData structure, initializes fields to zero on first call.
// Likely used to manage profiler counters (e.g., frame time, draw calls) for the EA EARS engine debug overlay.

#include <cstdint>

// Forward declaration for the static method
class ProfilerState {
public:
    static struct ProfilerData* getInstance();
};

// Data layout at 0x01223d00: 4 consecutive int32 fields
struct ProfilerData {
    int32_t field0; // +0x00
    int32_t field4; // +0x04
    int32_t field8; // +0x08
    int32_t fieldC; // +0x0c
};

// Global flag at 0x01223d10, bit 0 indicates initialization
static uint32_t s_profilerInitialized = 0;

// Global singleton instance at 0x01223d00
static ProfilerData s_profilerData = {0, 0, 0, 0};

ProfilerData* ProfilerState::getInstance() {
    // Check if already initialized via bit 0 of global flag
    if ((s_profilerInitialized & 1) == 0) {
        // Mark as initialized
        s_profilerInitialized |= 1;
        // Zero out all fields
        s_profilerData.field0 = 0;
        s_profilerData.field4 = 0;
        s_profilerData.field8 = 0;
        s_profilerData.fieldC = 0;
    }
    return &s_profilerData;
}