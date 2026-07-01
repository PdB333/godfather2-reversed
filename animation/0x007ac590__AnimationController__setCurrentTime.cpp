// FUNC_NAME: AnimationController::setCurrentTime

void __thiscall AnimationController::setCurrentTime(float newTime)
{
    // If the new time differs from the current time, mark the dirty flag and update.
    if (newTime != m_currentTime) // +0x14
    {
        m_dirtyFlag = 1; // +0x64 (byte), indicates property changed
        m_currentTime = newTime; // +0x14
    }
}