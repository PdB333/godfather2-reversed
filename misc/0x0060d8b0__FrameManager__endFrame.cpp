// FUNC_NAME: FrameManager::endFrame
// Address: 0x0060d8b0
// This function finalizes a frame: captures elapsed time, updates accumulated time,
// handles a time-based processing callback, increments frame counter, and resets timers.
// Parameter 'updateTime': if 0 and gTimeProcessingObject is valid, calls processAccumulatedTime().

#include <cstdint>

// Global 64-bit accumulated frame time (low, high)
extern uint32_t gFrameTimeLow;   // DAT_01205828
extern uint32_t gFrameTimeHigh;  // DAT_0120582c

// Global pointer to a time-processing object (e.g. frame rate limiter)
extern void* gTimeProcessingObject; // DAT_00f15a48

// Frame counter
extern uint32_t gFrameCount;     // DAT_01205874

// Another pointer used for profiling cleanup
extern void* gProfilingData;     // DAT_00f15a44

// Frame state flags cleared at end of frame
extern uint32_t gFrameFlag1;     // DAT_012058b0
extern uint32_t gFrameFlag2;     // _DAT_011f3918
extern uint32_t gFrameFlag3;     // _DAT_011f391c
extern uint32_t gFrameFlag4;     // _DAT_011f3920
extern uint32_t gFrameFlag5;     // _DAT_011f3924

// Forward declarations of helper functions
void profilingBegin(int32_t markerId);    // FUN_00609890
void resetFrameTimers();                  // FUN_0060dcb0
int64_t getHighResolutionTime();          // FUN_00494ad0
void processAccumulatedTime(void* obj);   // FUN_00608ca0
void updateFrameRate();                   // FUN_00608e90
void profilingEnd(void* data);            // FUN_00609810
void finalizeEngineState();               // FUN_00422800

void FrameManager::endFrame(char updateTime)
{
    int64_t timeDelta;
    int64_t timeStart;
    int64_t timeEnd;
    int64_t accumulatedTime;

    // Begin profiling marker (profile block start)
    profilingBegin(1);

    // Reset per-frame timers (e.g., start of timing window)
    resetFrameTimers();

    // Capture start and end timestamps
    timeStart = getHighResolutionTime();
    timeEnd = getHighResolutionTime();

    // Calculate elapsed time: (end - start) + previous accumulated time
    accumulatedTime = (timeEnd - timeStart) + ((int64_t)gFrameTimeHigh << 32 | gFrameTimeLow);

    // Store new accumulated time
    gFrameTimeLow = (uint32_t)(accumulatedTime & 0xFFFFFFFF);
    gFrameTimeHigh = (uint32_t)(accumulatedTime >> 32);

    // If updateTime is zero and we have a time-processing object, process accumulated time
    if ((updateTime == 0) && (gTimeProcessingObject != nullptr))
    {
        processAccumulatedTime(gTimeProcessingObject);

        // Re-read accumulated time (might have been modified by callback)
        accumulatedTime = (int64_t)gFrameTimeHigh << 32 | gFrameTimeLow;
    }

    // Re-store accumulated time (idempotent if unchanged)
    gFrameTimeLow = (uint32_t)(accumulatedTime & 0xFFFFFFFF);
    gFrameTimeHigh = (uint32_t)(accumulatedTime >> 32);

    // Update frame rate calculations
    updateFrameRate();

    // Increment frame counter
    gFrameCount++;

    // Reset timers again for next frame
    resetFrameTimers();

    // End profiling marker
    profilingEnd(gProfilingData);

    // Clear per-frame state flags
    gFrameFlag1 = 0;
    gFrameFlag2 = 0;
    gFrameFlag3 = 0;
    gFrameFlag4 = 0;
    gFrameFlag5 = 0;

    // Finalize engine state (e.g., swap buffers, reset temp data)
    finalizeEngineState();
}