// FUNC_NAME: Entity::getScaledTimerValue
int __thiscall Entity::getScaledTimerValue(void* this) {
    undefined4 resultHandle; // possibly a handle or object ID
    int timerExists;
    float timerValue;
    undefined1 outputBuffer[4];

    timerValue = 0.0f;
    resultHandle = findObjectByName(&s_timerObjectName, outputBuffer); // 0x004dafd0
    timerExists = getTimer(resultHandle, outputBuffer); // 0x005e9d90, returns non-zero if timer found

    if ((timerExists != 0) && (*(int*)((int)this + 0x580) != 0)) { // +0x580: some active flag or pointer
        lockMutex();                    // 0x00c9eac0
        readTimerValue(2, &timerValue); // 0x00c9cd00, reads timer into timerValue
        unlockMutex();                  // 0x00c9eae0
    }
    return (int)(timerValue * g_timeScale); // 0x00e2e230: global time scale factor
}