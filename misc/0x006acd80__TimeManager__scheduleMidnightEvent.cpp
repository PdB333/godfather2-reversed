// FUNC_NAME: TimeManager::scheduleMidnightEvent
int __fastcall TimeManager::scheduleMidnightEvent(void* thisPtr)
{
    int result;
    int minutesUntilMidnight;
    int hours, mins;
    char timeBuffer[8]; // Pointed to by FUN_00826510 to fill time struct

    result = 0;
    if (g_timeSystemActive)
    {
        getCurrentTimeStruct(timeBuffer); // Fills timeBuffer with hours (offset 0?) and mins (offset 4?) – layout not confirmed
        // After the call, stack variables hours and mins are set from the buffer – Ghidra reassembly shows local_c = hours, local_8 = mins
        if (thisPtr == 0)
        {
            // Not used, just a placeholder; but actually thisPtr is used in the next call
        }
        else
        {
            // offset +0x4 likely vtable or some object pointer
            // offset +0x3F0 likely a callback or timer event data (1008 bytes into object)
            // Compute minutes until midnight: (24 - hours)*60 - minutes
            // hours and mins are read from the local vars set by getCurrentTimeStruct
            minutesUntilMidnight = (0x18 - hours) * 0x3c - mins;
            setTimer(minutesUntilMidnight, (int)thisPtr + 0x3F0, (int)thisPtr + 4, 0);
        }
        result = 1;
    }
    return result;
}