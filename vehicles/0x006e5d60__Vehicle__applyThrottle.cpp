// FUNC_NAME: Vehicle::applyThrottle
void __thiscall Vehicle::applyThrottle(float throttleInput) {
    // Global scaling factors: DAT_00e445c8 likely g_speedMultiplier, _DAT_00d5c458 likely g_timeScale
    double scaledValue = (double)(throttleInput * g_speedMultiplier * g_timeScale);

    // Call engine update (synchronizes frame state, e.g., Havok simulation step)
    EARS::Core::updateScene();

    // Store computed speed at +0x54 (m_currentSpeed)
    this->m_currentSpeed = (float)scaledValue;
}