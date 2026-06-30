// FUNC_NAME: initHighResTimer

#include <windows.h>

// Global variables (initialized at startup)
extern bool gPerfCounterAvailable;       // DAT_01223370
extern double gPerfCounterDivisor;       // DAT_00e44570 (constant multiplier, e.g., 1.0 for seconds, 1000.0 for ms)
extern double gPerfCounterToSeconds;     // _DAT_01223368

// Query the high-resolution performance counter frequency and store the conversion factor
double* initHighResTimer()
{
    LARGE_INTEGER freq;
    BOOL success = QueryPerformanceFrequency(&freq);
    gPerfCounterAvailable = (success != 0);
    gPerfCounterToSeconds = gPerfCounterDivisor / (double)(long long)freq.QuadPart;
    return &gPerfCounterToSeconds;
}