// FUNC_NAME: DebugManager::outputMessage
void __thiscall DebugManager::outputMessage(DebugManager* this)
{
    const char* message;
    int handle;
    
    // +0x2108: pointer to message string, or default if null
    message = *(const char**)((int)this + 0x2108);
    if (message == (const char*)0x0) {
        message = &DAT_0120546e;  // Default empty/placeholder string
    }
    
    // +0x2104: output handle (file descriptor, console, or similar)
    handle = *(int*)((int)this + 0x2104);
    
    // Write the message to the given output handle
    FUN_00737940(handle, message);
}