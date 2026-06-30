// FUNC_NAME: AnimTimeline::processTimelineEvents

// Function at 0x00631e10 - Processes timeline events from an input buffer and writes adjusted events to an output buffer.
// Assumes the timeline events have a structure: type (int) and time (float).
// Types: 3 = normal time event, 4 = event that gets its time from an external function (likely current game time).
// The global g_timelineMultiplier scales the time values.
// The global g_timelineSentinel is a float sentinel that triggers a wait loop until a valid event appears.
// The input buffer pointer is at +0x0c, output buffer pointer at +0x08.
// Each event is 8 bytes.

// External globals
extern float g_timelineMultiplier;  // _DAT_00e449b0
extern float g_timelineSentinel;   // DAT_00e2b05c

// External function prototypes
extern int getCurrentTime(float *outTime);  // FUN_00636850 - returns 1 if successful
extern void logError(const char *msg);      // FUN_00627ac0 - uses a string pointer

int __thiscall AnimTimeline::processTimelineEvents(int thisPtr)
{
    int *inputPtr;
    int *outputPtr;
    float currentTime;
    int *eventPtr;
    float adjustedTime;

    // Read the current input pointer
    inputPtr = *(int **)(thisPtr + 0x0c);
    outputPtr = *(int **)(thisPtr + 0x08);

    // If output pointer is already >= input pointer, or input pointer is null, return early with time=0
    if (outputPtr >= inputPtr)
        goto set_time_zero;

    if (inputPtr == 0)
        goto set_time_zero;

    // Check the type of the current input event
    if (*inputPtr != 3)
    {
        if (*inputPtr != 4)
            goto set_time_zero;

        // Type 4: need to get current time from game
        if (getCurrentTime(&currentTime) == 0)
            goto set_time_zero;

        // Create a local event with type 3 and the current time
        eventPtr = &currentTime; // reinterpreted as a pointer to an event? Actually, the code sets local_10=3; local_c=currentTime; then piVar3 = &local_10;
        // So it points to a local event structure (type=3, time=currentTime)
        int localEvent[2];
        localEvent[0] = 3;
        localEvent[1] = *(int*)&currentTime;
        eventPtr = localEvent;
    }
    else
    {
        // Type 3: use the time from the input event directly
        currentTime = *(float *)(inputPtr + 1); // inputPtr[1] is the float time
    }

    // Now eventPtr points to a valid event of type 3 with a time value
    adjustedTime = *(float *)(eventPtr + 1); // the time value
    if (adjustedTime == g_timelineSentinel)
    {
        // If the time equals the sentinel, loop until a valid input event appears
        while (int *tempInput = *(int **)(thisPtr + 0x0c),
               outputPtr >= tempInput ||
               tempInput == 0 ||
               (*tempInput != 3 && (*tempInput != 4 || getCurrentTime(&currentTime) == 0)))
        {
            logError("number"); // PTR_s_number_00e2a8a8
            // Re-read output pointer (might change? but it's the same)
            outputPtr = *(int **)(thisPtr + 0x08);
        }
        // After the loop, we have a valid input event from the input buffer? Actually the loop doesn't advance inputPtr.
        // But after exit, the condition is false, meaning we have a valid event at the current inputPtr.
        // However, the code does not update eventPtr; it still uses the original eventPtr? That seems inconsistent.
        // Actually the loop condition uses the same logic as the initial check, so if we exit the loop, the current inputPtr is valid.
        // But the code after the loop still uses eventPtr from before the loop (which might be from a type 3 or 4 earlier).
        // This is ambiguous; likely the intent is to wait until the input buffer has a valid event, then proceed with that event.
        // But the decompiled code shows the loop condition checks inputPtr but does not reassign eventPtr.
        // This could be a decompilation artifact; the original might have had a "continue" or reassignment.
        // For reconstruction, we'll preserve the logic as per decompiled.
        // It's possible that eventPtr is still the same from before the loop (from a type 3 or the local event from type 4).
        // So we keep adjustedTime = eventPtr[1] from before.
    }

    // Apply the global multiplier
    adjustedTime = adjustedTime * g_timelineMultiplier;
    // Write the output event: type=3, time=adjustedTime
    int *out = *(int **)(thisPtr + 0x08);
    out[0] = 3;
    out[1] = *(int*)&adjustedTime;
    // Advance output pointer
    *(int *)(thisPtr + 0x08) = (int)out + 8;
    return 1;

set_time_zero:
    adjustedTime = 0.0f;
    // Note: The code falls through to the same output writing, but with time=0? Actually, when jumping to LAB_00631ecb, local_14 is set to 0.0, then it continues to the output write.
    // So we fall through to the output write block.
    // Write output event with type=3 and time=0
    int *out = *(int **)(thisPtr + 0x08);
    out[0] = 3;
    out[1] = 0;
    *(int *)(thisPtr + 0x08) = (int)out + 8;
    return 1;
}
```