// FUNC_NAME: DebugUtils::loadAndLogString
bool DebugUtils::loadAndLogString(void* resourceHandle, void* /*unused*/, uint32_t stringId)
{
    char buffer[2048]; // Buffer for reading string content
    bool result = readStringFromResource(resourceHandle, buffer, sizeof(buffer), stringId);
    if (result)
    {
        debugPrintString(buffer); // Output the string to debug console/log
    }
    return result;
}