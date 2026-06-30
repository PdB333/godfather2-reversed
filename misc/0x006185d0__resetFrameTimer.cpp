// FUNC_NAME: resetFrameTimer
// Address: 0x006185d0
// Role: Resets the frame timer by storing a copy of the raw frame time and zeroing the elapsed time counter.

// Global variables (inferred from Ghidra data references)
extern uint32_t g_rawFrameTime;          // DAT_01205750
extern uint32_t g_currentFrameTime;      // DAT_0120595c
extern uint64_t g_elapsedFrameTime;      // _DAT_011f7440 (two 32-bit halves at 0x011f7440 and 0x011f7448)

// Forward declaration of helper function called after reset
void updateFrameTimer(void);             // FUN_00609bf0

void resetFrameTimer(void)
{
    // Store a snapshot of the raw frame time to serve as base for delta calculations
    g_currentFrameTime = g_rawFrameTime;

    // Reset the elapsed time accumulator (0x011f7440 and 0x011f7448)
    g_elapsedFrameTime = 0;

    // Update internal timer state after reset
    updateFrameTimer();
}