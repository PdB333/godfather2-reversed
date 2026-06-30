// FUNC_NAME: DebugManager::displayMessage
void __thiscall DebugManager::displayMessage(int this, char* message) {
    int logLevel;
    int unknownGlobal = DAT_00e2e37c; // global debug filter value

    if (*(int*)(this + 0x37c) == unknownGlobal) {
        if (message[0] != '\0') {
            logLevel = 2; // INFO
        } else {
            goto setLevel7;
        }
    } else {
        if (message[0] == '\0') {
setLevel7:
            logLevel = 7; // ERROR/WARNING
        } else {
            goto skipLogCall; // no logging when filter doesn't match and message non-empty
        }
    }
    FUN_009f4240(logLevel, 1, 0); // likely Engine::logMessage(logLevel, category, flags)

skipLogCall:
    // If debug overlay is active and auto-close flag is set, close debug console when message is empty
    if ((*(char*)(this + 0x39c) != '\0') && ((*(unsigned char*)(this + 0x39e) >> 1 & 1) != 0) && (message[0] == '\0')) {
        FUN_0070ce60(0); // likely close debug console
    }
}