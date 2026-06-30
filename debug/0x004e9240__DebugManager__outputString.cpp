// FUNC_NAME: DebugManager::outputString
void __fastcall DebugManager::outputString(int severity, const char* message)
{
    // Compute string length excluding null terminator
    const char* end = message;
    while (*end != '\0')
    {
        ++end;
    }
    int lengthMinusOne = (end - message) - 1; // strlen - 1

    // Write the message with the computed length (possibly excludes the null)
    FUN_00ab8560(severity, message, lengthMinusOne);
    FUN_00616720();
}