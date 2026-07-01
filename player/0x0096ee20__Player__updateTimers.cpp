//FUNC_NAME: Player::updateTimers
void __fastcall Player::updateTimers(int thisPtr)
{
    char conditionResult;

    // +0x700: float m_mainTimer
    // +0x704: bool m_flagActive
    // +0x6fc: float m_cooldownTimer
    // Global: g_gameTime (float), g_timerDecrement (float), g_timerThreshold (float), g_timerIncrement (float)

    if (g_gameTime < *(float *)(thisPtr + 0x700)) {
        *(float *)(thisPtr + 0x700) -= g_timerDecrement;
    }

    if (*(char *)(thisPtr + 0x704) != 0 && *(float *)(thisPtr + 0x6fc) <= g_timerThreshold) {
        conditionResult = checkTimerCondition();
        if (conditionResult != 0) {
            *(char *)(thisPtr + 0x704) = 0;
            return;
        }
        *(float *)(thisPtr + 0x6fc) = g_timerThreshold + g_timerIncrement;
    }
}