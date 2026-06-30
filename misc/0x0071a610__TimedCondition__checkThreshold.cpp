// FUNC_NAME: TimedCondition::checkThreshold
bool __fastcall TimedCondition::checkThreshold(TimedCondition* this) {
    // +0x44 = m_lastEventTime (float)
    // Global g_currentTime (DAT_01205228) and g_minTimeDelta (DAT_00d5ef70)
    if (g_currentTime - this->lastEventTime_0x44 < g_minTimeDelta) {
        return true;
    }
    return false;
}