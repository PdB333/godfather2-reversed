// FUNC_NAME: Timer::update
float __thiscall Timer::update(float delta, int callbackParam) {
    // If a callback pointer exists, invoke it with the delta and parameter
    if (m_pCallback != 0) {
        FUN_00892490(delta, callbackParam);
    }

    // Advance the timer by delta
    float newTime = m_fCurrentTime + delta;

    // Clamp the timer to the global min/max range
    float minTime = DAT_00d7bcac;
    float maxTime = DAT_00d7bca8;
    if (newTime <= minTime) {
        newTime = minTime;
    } else if (maxTime <= newTime) {
        newTime = maxTime;
    }

    // Store the clamped time
    m_fCurrentTime = newTime;

    return newTime;
}