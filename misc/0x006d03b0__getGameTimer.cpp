// FUNC_NAME: getGameTimer
long double getGameTimer() {
    // Global variable at 0x00e51118 (possibly TimeManager::s_currentTime)
    return *(long double*)0x00e51118;
}