// FUNC_NAME: Profiler::measureSection
undefined4 Profiler::measureSection(undefined4 param_1, undefined4 param_2, ushort param_3, undefined4 param_4)
{
    // Use QueryPerformanceCounter for high-resolution timing
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    // Prepare a parameter structure on the stack (likely for object construction)
    undefined4 stackParams[4]; // uStack_8c, uStack_88, uStack_84, uStack_80
    stackParams[0] = 2;       // +0x00: size or type
    stackParams[1] = 0x10;    // +0x04: flags?
    stackParams[2] = 0;       // +0x08: extra

    // Allocate a profiler sample object (vtable call via DAT_01205868)
    // The first argument is an ID/size computed from in_AX and unaff_EDI
    undefined4 sampleObj = (**(code **)*DAT_01205868)((uint)in_AX * unaff_EDI, &stackParams);

    // Overwrite the stack-based parameter struct with actual arguments
    stackParams[1] = param_2;  // +0x04
    stackParams[3] = (uint)param_3; // +0x0C (param_3 is a ushort)
    stackParams[2] = param_4;  // +0x08
    stackParams[4] = sampleObj; // +0x10 (unused beyond this point?)

    // Initialize the profiler sample (likely sets up callbacks)
    FUN_0061cea0();
    FUN_0061cc20();

    // Release/destroy the profiler sample object (vtable+4 call)
    (**(code **)(*DAT_01205868 + 4))(sampleObj, 0);

    // Capture end time and accumulate into global 64-bit profiler counters
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);

    // Compute delta (using register variables derived from QPC results)
    uint deltaLow = (uint)(endTime.QuadPart - startTime.QuadPart); // approximated
    uint deltaHigh = (uint)((endTime.QuadPart >> 32) - (startTime.QuadPart >> 32)) + (uint)(deltaLow < (endTime.QuadPart & 0xFFFFFFFF));

    // Global 64-bit accumulator (g_profilerTimeLow, g_profilerTimeHigh)
    bool carry = CARRY4(g_profilerTimeLow, deltaLow);
    g_profilerTimeLow += deltaLow;
    g_profilerTimeHigh += deltaHigh + (uint)carry;

    return 1;
}