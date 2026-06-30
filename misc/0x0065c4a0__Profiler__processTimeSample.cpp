// FUNC_NAME: Profiler::processTimeSample
// Address: 0x0065c4a0
// Role: Processes a high-precision timing sample for performance profiling.
//       Depending on global profiling mode, either logs the sample (mode 1) or
//       increments a counter and potentially triggers a debug break (mode 2).
//       The sample is scaled by a global multiplier if enabled.

// Note: All global variables are from static class members or global state.
// These names are inferred from the decompiled logic.

void Profiler::processTimeSample(int64_t rawTimeTicks) {
    // Global profiling mode: 0 = off, 1 = log, 2 = break on count
    static int gProfilingMode = 0;          // DAT_01205a68
    static bool gProfilingEnabled = false;  // DAT_0120589a (char bool)
    static bool gUseTimeScale = false;      // DAT_01223370
    static double gTimeScale = 1.0;         // _DAT_01223368
    static uint32_t gLogFlags = 0;          // _DAT_01226728
    static char* gLogStringA = nullptr;     // DAT_01226710 and DAT_0122671c
    static int gLogStringIdA = -1;          // DAT_01226714 and DAT_01226720
    static void* gPreviousLogHandler = nullptr; // DAT_01226718 and DAT_01226724
    static void* gCurrentLogHandler = nullptr;  // DAT_01205a84
    static int gBreakThreshold = 0;         // DAT_01205a7c (if >0, break when count >= threshold)
    static int gSampleCount = 0;            // DAT_01205a80
    static int gMaxSampleCount = 0;         // DAT_01205a6c
    static bool gSomeFlag = false;          // DAT_01127d3c
    static int gSomeCounter = 0;            // DAT_01127d38

    // Branch based on profiling mode and enable flag
    if (gProfilingMode != 2 || !gProfilingEnabled) {
        // Mode is not break-on-count or profiling is disabled
        double timeMs = (double)rawTimeTicks;
        if (gUseTimeScale) {
            timeMs *= gTimeScale;  // Scale time (e.g., convert ticks to ms)
        }

        if (gProfilingMode == 1 && gProfilingEnabled) {
            // Mode 1: Log the sample
            if ((gLogFlags & 2) == 0) {
                gLogFlags |= 2;
                gLogStringA = "getHighPrecisionMilliseconds"; // DAT_01226710
                // gLogStringIdA = -1; already -1
                gPreviousLogHandler = gCurrentLogHandler; // DAT_01226718 = DAT_01205a84
                gCurrentLogHandler = &gLogStringA;        // DAT_01205a84 = &DAT_01226710
            }
            // Log the time sample
            logWrite(&gLogStringA); // FUN_0065f6b0
            double local_c = timeMs;
            logStore(0x40, &local_c); // FUN_0064b810 - writes 0x40 bytes?
            logFlush(); // FUN_0065fab0
        }
        return;
    }

    // Mode 2: Break on count
    if ((gLogFlags & 1) == 0) {
        gLogFlags |= 1;
        gLogStringA = "getHighPrecisionMilliseconds"; // DAT_0122671c (different instance)
        // gLogStringIdA = -1;
        gPreviousLogHandler = gCurrentLogHandler; // DAT_01226724 = DAT_01205a84
        gCurrentLogHandler = &gLogStringA;        // DAT_01205a84 = &DAT_0122671c
    }
    logWrite(&gLogStringA); // FUN_0065f6b0

    gSampleCount++;
    if (gBreakThreshold != 0 && gSampleCount >= gBreakThreshold) {
        // Trigger breakpoint (software interrupt 3)
        void (*breakHandler)() = (void (*)())swi(3);
        (*breakHandler)();
        return;
    }

    // Store the raw sample value
    logLoad(0x40, &timeMs); // FUN_0064b9e0 - reads 0x40 bytes? Actually it's reversed: param order suggests store/load?

    if (!gSomeFlag && gSomeCounter < gMaxSampleCount) {
        return; // No break if conditions not met
    }
    // Otherwise, trigger breakpoint again
    void (*breakHandler)() = (void (*)())swi(3);
    (*breakHandler)();
    return;
}

// Helper function declarations (inferred from callees)
void logWrite(void* logString);          // FUN_0065f6b0
void logStore(int size, void* data);     // FUN_0064b810
void logFlush();                         // FUN_0065fab0
void logLoad(int size, void* data);      // FUN_0064b9e0 (note: order reversed)
void swi(int interrupt);                 // Software interrupt instruction