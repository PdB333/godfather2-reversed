// FUNC_NAME: TimerManager::checkTimerExpired
void TimerManager::checkTimerExpired(void)
{
    // Check if current state differs from target state
    if ((g_currentState != g_targetState) &&
        // Decrement timer by delta time and check if expired
        (g_timer -= g_deltaTime, g_timer <= 0.0f))
    {
        // Timer expired, trigger action with current state
        triggerAction(g_currentState);
    }
}