// FUNC_NAME: initSimpleTimer
// Function address: 0x005c0a30
// Initializes a simple timer structure with a default 1000ms duration.
// Used by various gameplay systems (e.g., event timers, cooldowns).

struct SimpleTimer
{
    int startTime;      // +0x00, time when timer started or reset
    int accumulatedTime; // +0x04, time elapsed (e.g., while paused)
    int unknown1;       // +0x08, always zeroed
    int unknown2;       // +0x0C, always zeroed
    int maxDuration;    // +0x10, duration in milliseconds (set to 1000)
    bool isActive;      // +0x14, timer active flag (set to true)
    int unknown3;       // +0x18, always zeroed
};

void __thiscall initSimpleTimer(SimpleTimer *timer)
{
    timer->startTime = 0;
    timer->accumulatedTime = 0;
    timer->unknown1 = 0;
    timer->unknown2 = 0;
    timer->maxDuration = 1000;
    timer->isActive = true;
    timer->unknown3 = 0;
}