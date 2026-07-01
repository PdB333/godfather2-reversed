// FUNC_NAME: DebugManager::setCurrentActionName
void DebugManager::setCurrentActionName(void* unusedThis, void* object) {
    char isActionActive = isActionActive(object); // FUN_008f6670
    if (isActionActive != 0) {
        if (object != 0) {
            // +0x3c is likely a const char* name field in the object
            setDebugString(&g_currentActionName, *(const char**)((int)object + 0x3c), 0);
            return;
        }
        setDebugString(&g_currentActionName, 0, 0);
    }
}