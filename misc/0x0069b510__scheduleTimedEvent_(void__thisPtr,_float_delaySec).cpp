// FUNC_NAME: scheduleTimedEvent (void* thisPtr, float delaySec)
// Function address: 0x0069b510
// Purpose: Schedules a timed callback via timer system, then performs additional processing.

struct TimerCallbackInfo {
    int timerHandle;         // +0x00
    int unknownFlag;         // +0x04
    int padding;             // +0x08
    void (*callback)(int);   // +0x0C
};

void scheduleTimedEvent(void* thisPtr, float delaySec)
{
    // Combined struct for timer info; stack layout: timerInfo (12 bytes) + callback pointer (4 bytes)
    struct LocalTimerData {
        int fields[3];        // 0x00-0x0B: timer handle, flag, padding
        void (*onFinish)(int); // 0x0C: function pointer called when timer fires
    } timerData;

    // Zero out the struct
    timerData.fields[0] = 0;
    timerData.fields[1] = 0;
    timerData.fields[2] = 0;
    timerData.onFinish = nullptr;

    // Schedule the callback: passes pointer to timerData, a string identifier (DAT_00d5cee4), and delay
    FUN_004d4ad0(&timerData, (const char*)0x00d5cee4, (double)delaySec);

    // Additional processing after scheduling timer
    FUN_0069b380();
    FUN_004d3e20();

    // If the timer was successfully scheduled, invoke the callback with the timer handle
    if (timerData.fields[0] != 0) {
        timerData.onFinish(timerData.fields[0]);
    }
}