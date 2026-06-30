// FUNC_NAME: Timer::isFinished
// 0x006f4d40 - Timer method: returns true if the stored duration <= given currentTime and the active flag is cleared.
bool __thiscall Timer::isFinished(float currentTime) const
{
    // +0x0C: float duration (time limit)
    // +0x10: char activeFlag (0 = inactive/finished)
    return (this->duration <= currentTime) && (this->activeFlag == 0);
}