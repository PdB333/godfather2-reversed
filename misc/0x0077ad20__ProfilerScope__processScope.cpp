// FUNC_NAME: ProfilerScope::processScope
void __thiscall ProfilerScope::processScope(int someArg1, int someArg2, char bEnterOrExit) {
    char bEnter = bEnterOrExit;
    if (this->m_state == 0xb) {
        debugLogString(g_enterString);
        if (bEnter != 0) {
            g_profilerDepth++;
            profilerUpdate();
        }
        debugLogString(g_stateNames[this->m_state * 2]);
        if (this->m_pCallbackEnter != 0) {
            (*(void (__thiscall **)(void*, int, int, char))(**(int**)this->m_pCallbackEnter + 0x10))(this->m_pCallbackEnter, someArg1, someArg2, bEnter);
        }
    }
    else {
        debugLogString(g_enterString);
        if (bEnter != 0) {
            g_profilerDepth++;
            profilerUpdate();
        }
        if (this->m_pCallbackEnter != 0) {
            (*(void (__thiscall **)(void*, int, int, char))(**(int**)this->m_pCallbackEnter + 0x10))(this->m_pCallbackEnter, someArg1, someArg2, bEnter);
        }
        debugLogString(g_exitString);
        if (bEnter != 0) {
            profilerUpdate();
        }
        debugLogString(g_stateNames[this->m_state * 2]);
        debugLogString(g_exitString);
        if (bEnter != 0) {
            profilerUpdate();
        }
        if (this->m_pCallbackExit != 0) {
            (*(void (__thiscall **)(void*, int, int, char))(**(int**)this->m_pCallbackExit + 0x10))(this->m_pCallbackExit, someArg1, someArg2, bEnter);
        }
    }
    if (bEnter != 0) {
        g_profilerDepth--;
        profilerUpdate();
    }
    debugLogString(g_enterString); // Likely a trailing newline or flush
    return;
}