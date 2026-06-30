// FUNC_NAME: TimerComponent::update
void TimerComponent::update(float deltaTime)
{
    float maxTimer = g_maxTimer; // DAT_00e2d99c - maximum timer value
    if (this != nullptr &&
        g_enableThreshold < static_cast<float>(reinterpret_cast<uint32_t&>(this->m_rate) & g_rateMask)) // DAT_00e44598, DAT_00e44680
    {
        // Update timer: deltaTime * timeScale * rate
        this->m_timer += deltaTime * g_timeScale * this->m_rate; // +0x54 timer, +0x58 rate, g_timeScale = DAT_00e2b050

        // Clamp timer between 0 and maxTimer
        if (this->m_timer > 0.0f)
        {
            if (this->m_timer > maxTimer)
                this->m_timer = maxTimer;
        }
        else
        {
            this->m_timer = 0.0f;
        }

        // If timer reached a boundary (0 or max), trigger callbacks
        if (this->m_timer == 0.0f || this->m_timer == maxTimer)
        {
            onTimerExpired(this->field_100, this->field_0x5c, this->field_0x65); // FUN_005dbc10
            onTimerComplete(); // FUN_005f3640
            this->field_0x67 = 0xFF; // flag to indicate timer finished
        }
    }
}