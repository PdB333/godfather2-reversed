// FUNC_NAME: CGameObject::debugLogTick
void __thiscall CGameObject::debugLogTick(void)
{
    // Get some system time/tick value (likely milliseconds or frame count)
    int tickValue = GetSystemTick(); // FUN_00471610 - returns current tick/time

    // Check if logging flag at +0x50 is set (m_bLoggingEnabled)
    if (*(int *)(this + 0x50) != 0) {
        // Write log message:
        //  - log context pointer (possibly a static log buffer/manager)
        //  - log level/category 0x65 (101, e.g., LOG_DEBUG)
        //  - formatted data: tickValue + 0x30 (some offset)
        //  - timeout/infinite (-1)
        WriteLog(&g_logContext, 0x65, tickValue + 0x30, -1); // FUN_00805a10
    }
}