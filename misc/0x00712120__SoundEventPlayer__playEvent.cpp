// FUNC_NAME: SoundEventPlayer::playEvent
// Address: 0x00712120
// Role: Manages the lifecycle of sound/animation events: stops current, starts new, tracks timing offsets.

// Member offsets (from this pointer):
// +0x58 : m_requestCount (int)           - incremented on each call
// +0x5c : m_currentEvent (SoundEventHandle*) - currently active event
// +0x60 : m_forceRestart (char/bool)     - if true, reset accumulated time and overwrite startTime
// +0x64 : m_startTime (undefined4)       - copied from param_4 when no event active or force restart
// +0x68 : m_accumulatedTime (float)      - total playback offset from previous events

// SoundEventHandle layout (partial):
// +0x14 : m_duration (float)             - length of the event in seconds

void __thiscall SoundEventPlayer::playEvent(int this, int param2, int param3, float param4, int param5)
{
    int currentEvent;
    float fVar1;

    // Increment request counter (e.g., for debug logging or sequence tracking)
    *(int *)(this + 0x58) = *(int *)(this + 0x58) + 1;

    currentEvent = *(int *)(this + 0x5c);
    if (currentEvent == 0) {
        // No current event: store the start time directly from param4
        *(undefined4 *)(this + 0x64) = *(undefined4 *)&param4;
    } else {
        if (*(char *)(this + 0x60) == '\0') {
            // Normal case: add previous event's duration to accumulated time
            fVar1 = *(float *)(currentEvent + 0x14) + *(float *)(this + 0x68);
        } else {
            // Force restart: overwrite start time and reset accumulated time
            *(undefined4 *)(this + 0x64) = *(undefined4 *)&param4;
            fVar1 = 0.0f;
        }
        *(float *)(this + 0x68) = fVar1;

        // Release the previous event (destructor/stop)
        SoundEventPlayer::releaseEvent(currentEvent);
        *(int *)(this + 0x5c) = 0;
    }

    // Create a new event using the provided parameters
    currentEvent = SoundEventPlayer::createEvent(param2, param3, param4, param5);
    *(int *)(this + 0x5c) = currentEvent;
    if (currentEvent != 0) {
        SoundEventPlayer::initializeEvent(currentEvent);
    }

    // Clear the force-restart flag
    *(char *)(this + 0x60) = '\0';
}