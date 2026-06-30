// FUNC_NAME: DebugManager::logStartupMessage
void __thiscall DebugManager::logStartupMessage()
{
    // +0x10 = state (0=inactive, 1=loading, 2=ready, 3=active)
    if (g_bDebugMode)
    {
        // Initialize local string buffer (9 bytes: pointer + int + char?)
        char buffer[12];
        *(int*)buffer = g_szDefaultString;   // copy global string reference
        *(int*)(buffer + 4) = 0;             // zero length/offset?
        buffer[8] = 0;

        // FUN_00408a00 – likely a string initialization or copy
        stringInitialize(buffer, 0);

        // Load a resource string via helper (FUN_0068cc40)
        // Returns a struct with data pointer, size, flags, and destructor
        ResourceString resString;
        char result = loadResourceString(&resString);

        // Use resource string or a fallback empty string
        char* printStr = resString.data;
        if (printStr == nullptr)
        {
            printStr = g_szEmptyString;   // "+0x00" global
        }

        // FUN_00983120 – debug/log output function
        debugOutputString(printStr, 0, result);

        // Mark object as active
        this->state = 3;

        // Free resource if allocated
        if (resString.data != nullptr)
        {
            resString.destructor(resString.data);
        }
    }
}