// FUNC_NAME: TimedObject::isWithinTimeWindow

bool __thiscall TimedObject::isWithinTimeWindow(float referenceTime)
{
    // g_currentGameTime is a global float representing some game time (e.g., elapsed seconds)
    // m_startTime is stored at +0x1c in this object (e.g., the start of a timed event)
    // g_eventDuration is a global constant float representing the allowed window duration

    if (g_currentGameTime <= m_startTime &&
        (referenceTime - m_startTime) <= g_eventDuration)
    {
        return true;
    }
    return false;
}