// FUNC_NAME: scheduleTimerForObject
// Address: 0x006acd80
// This function appears to schedule a timer event based on current time.
// It uses a global flag to check if the timer system is ready.
// The caller passes a pointer (param_1) to an object (likely a game entity or timer client) that contains
//   a timer-related member at offset +0x3F0 (e.g., a timer ID or callback list) and a context pointer at +4.
// The function computes a delay (in minutes) until midnight and sets a timer callback.

bool __fastcall scheduleTimerForObject(void* pObject)
{
    // Global readiness flag for the timer system (0 = not ready)
    if (g_bTimerSystemReady == 0) {
        return false;
    }

    // Retrieve current system time into a local structure (presumably hours, minutes)
    // localTimeBuf is 8 bytes; local_hours and local_minutes are consecutive ints after it.
    byte localTimeBuf[8]; // actual layout may vary, but we assume it's a time structure
    int local_hours;
    int local_minutes;

    getCurrentTime(localTimeBuf); // Fills localTimeBuf, local_hours, local_minutes

    // Compute minutes until midnight: (24 - current_hour) * 60 - current_minute
    int minutesUntilMidnight = (24 - local_hours) * 60 - local_minutes;

    // Determine the context pointer:
    // If pObject is null, no context; otherwise use pObject+4 (e.g., owner reference)
    void* pContext;
    if (pObject == 0) {
        pContext = 0;
    } else {
        pContext = (void*)((int)pObject + 4);
    }

    // Schedule the timer:
    //   - First argument: pointer to timer-related member at offset 0x3F0 (e.g., timer array/list)
    //   - Second argument: delay in minutes
    //   - Third argument: context pointer (or 0 if no object)
    //   - Fourth argument: flags (0)
    schedulerAddTimer((int)pObject + 0x3F0, minutesUntilMidnight, (int)pContext, 0);

    return true;
}