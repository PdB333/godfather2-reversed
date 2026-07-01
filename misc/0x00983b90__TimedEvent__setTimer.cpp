// FUNC_NAME: TimedEvent::setTimer
void __thiscall TimedEvent::setTimer(TimedEvent *this, int startTime)
{
    uint deadline;
    int callbackDataSize;

    // Store the start time (likely in milliseconds)
    this->startTime = startTime;
    
    // Calculate deadline as startTime + (current simulation time in seconds)
    // DAT_01205224 is g_simTimeMs (current sim time in ms)
    // Dividing by 1000 converts to seconds; adding to startTime gives absolute deadline
    deadline = (uint)(g_simTimeMs / 1000) + startTime;
    this->deadline = deadline;
    
    // Copy callback data from this->callbackData to this->backupCallbackData
    // DAT_00d5f520 is g_callbackDataSize (size of the callback data structure)
    // The flags 0 and 4 likely indicate memory copy mode or alignment
    callbackDataSize = g_callbackDataSize;
    copyCallbackData(this->backupCallbackData, this->callbackData, callbackDataSize, 0, 4);
}