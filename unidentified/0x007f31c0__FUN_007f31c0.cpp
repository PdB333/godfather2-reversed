// FUNC_NAME: SomeClass::getNormalizedTimeSinceEvent
float __thiscall getNormalizedTimeSinceEvent(int this, float currentTime)
{
    float elapsed = currentTime - *(float *)(this + 0x10); // +0x10: eventStartTime
    if (elapsed < 0.0f) {
        return 0.0f;
    }
    return elapsed / *(float *)(this + 0xc); // +0xc: eventDuration
}