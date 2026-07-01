// FUNC_NAME: DebugManager::displayObjectName

void DebugManager::displayObjectName() {
    char nameBuffer[48];          // Temporary buffer for object name
    char debugBuffer[28];         // Debug output string buffer

    // Get object name from handle at this+0x38
    bool result = GetObjectName(*(int*)(this + 0x38), nameBuffer);
    if (result) {
        // Output debug string (likely filled/processed by PrintDebugString)
        PrintDebugString(debugBuffer);
    }
}