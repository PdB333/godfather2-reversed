// FUNC_NAME: Debug::printMessage
void Debug::printMessage(uint32 arg1, const char* message) {
    // arg1 is unused; the global DebugManager singleton is hardcoded at 0x012234bc
    // Assumed: DebugManager::outputMessage(const char* msg) at 0x005e4950
    ((DebugManager*)0x012234bc)->outputMessage(message);
    return;
}