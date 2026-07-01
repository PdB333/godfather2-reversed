// FUNC_NAME: DebugConsole::printTimerInfo
void __fastcall DebugConsole::printTimerInfo(DebugConsole* this) {
    char* timeStr = nullptr;
    char* bracketStr = nullptr;
    char* finalStr = nullptr;
    timeStr = nullptr;
    int unused1 = 0;
    int unused2 = 0;
    int unused3 = 0;
    bracketStr = nullptr;
    int unused4 = 0;
    int unused5 = 0;
    int unused6 = 0;

    if (*(int*)((uintptr_t)this + 0x8C) == 0) {
        // Format as HH:MM using total seconds
        uint totalSeconds = (*(uint*)((uintptr_t)this + 0xFC) + 500U) / 1000;
        formatTimeHMS(totalSeconds / 60, totalSeconds % 60, &timeStr);
        uint someHash = 0xC5E5D016;
    } else {
        uint someHash = 0x29981489;
        if ((*(byte*)((uintptr_t)this + 0xE8) & 1) == 0) {
            formatTimeColon(*(uint*)((uintptr_t)this + 0xFC), &timeStr, true);
        } else {
            formatTimeCompact(*(uint*)((uintptr_t)this + 0xFC), &timeStr, true);
        }
    }

    char* timeStrSafe = timeStr;
    if (timeStr == nullptr) {
        timeStrSafe = &emptyString; // DAT_0120546e
    }

    formatString(&bracketStr, "{B:%s}{#%d}", timeStrSafe, someHash);
    char* bracketStrSafe = bracketStr;
    if (bracketStr == nullptr) {
        bracketStrSafe = &emptyString;
    }

    // Copy final string for output
    copyString(&finalStr, bracketStrSafe);

    // Output debug line
    printNewline();
    printString(finalStr, 0, unused5);

    // Free strings
    if (finalStr != nullptr) {
        freeString(finalStr);
    }
    if (bracketStr != nullptr) {
        freeString(bracketStr);
    }
    if (timeStr != nullptr) {
        freeString(timeStr);
    }
}