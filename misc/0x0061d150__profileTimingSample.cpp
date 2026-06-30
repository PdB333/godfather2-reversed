// FUNC_NAME: profileTimingSample

/* Profile timing sample function, records elapsed time for a profiled block.
   Uses a global profiler object (gProfilerVTablePtr) to begin/end a sample.
   Accumulates total time in global 64-bit counter (gProfilerElapsed). */

#include <windows.h> // for LARGE_INTEGER, QueryPerformanceCounter

// Global profiler vtable pointer (points to object with two methods at offsets 0 and 4)
extern void** gProfilerVTablePtr; // formerly DAT_01205868

// Accumulated elapsed time (64-bit) from all samples
extern unsigned int gProfilerElapsedLow;  // formerly DAT_01205948
extern unsigned int gProfilerElapsedHigh; // formerly DAT_0120594c

// Called to start/stop a profiler block
void FUN_0061cea0(); // profilerPreBlock?
void FUN_0061cc20(); // profilerPostBlock?

int profileTimingSample(unsigned int param1, unsigned int param2, unsigned short param3, unsigned int param4)
{
    LARGE_INTEGER startTime;
    unsigned int tempSize;
    unsigned int tempType;
    unsigned int tempId;
    unsigned short tempFlags;
    unsigned int profilerObj;

    QueryPerformanceCounter(&startTime);

    // Build a temporary profiler block structure on the stack
    tempSize = 2;      // block size
    tempType = 0x10;   // block type
    tempId = 0;        // identifier

    // Call profiler begin method (vtable offset 0)
    profilerObj = ((int (__thiscall*)(unsigned int, unsigned int*))gProfilerVTablePtr[0])(param1, &tempSize);
    // Overwrite structure fields with provided parameters
    tempType = param2;
    tempFlags = param3;
    tempId = param4;
    // The profiler object handle is stored for later use

    FUN_0061cea0(); // probably profiler pre-process
    FUN_0061cc20(); // probably profiler post-process

    // Call profiler end method (vtable offset 4)
    ((void (__thiscall*)(unsigned int, int))gProfilerVTablePtr[1])(profilerObj, 0);

    // Capture end time and compute delta
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);

    // Compute elapsed ticks (64-bit)
    unsigned int deltaLow = (unsigned int)(endTime.LowPart) - (unsigned int)(startTime.LowPart);
    unsigned int deltaHigh = (unsigned int)(endTime.HighPart) - (unsigned int)(startTime.HighPart);
    bool carry = (endTime.LowPart < startTime.LowPart);
    if (carry) {
        deltaHigh--;
    }

    // Accumulate into global 64-bit counter
    unsigned int oldLow = gProfilerElapsedLow;
    unsigned int oldHigh = gProfilerElapsedHigh;
    unsigned int newLow = oldLow + deltaLow;
    unsigned int newHigh = oldHigh + deltaHigh;
    if (newLow < oldLow) { // carry from low addition
        newHigh++;
    }
    gProfilerElapsedLow = newLow;
    gProfilerElapsedHigh = newHigh;

    return 1;
}