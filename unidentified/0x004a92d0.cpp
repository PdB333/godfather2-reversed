// FUN_NAME: EAString::loadAndLogResource
void EAString::loadAndLogResource(int resourceId)
{
    EAString tempString; // struct at local_14 (8 bytes): offset +0 = char* data, +4 = uint16_t length, +6 = uint16_t capacity
    tempString.data = 0;
    tempString.length = 0;
    tempString.capacity = 0;

    // Initialize tempString from resource ID (likely EARS string table)
    EAString::fromResource(&tempString, resourceId); // FUN_00408260

    // Build a log structure (pointer to tempString's data, length, and a trailing zero byte)
    LogEntry logEntry;
    logEntry.text = tempString.data; // local_c (4 bytes)
    logEntry.textLength = 0;         // local_8 (4 bytes)
    logEntry.terminator = 0;         // local_4 (1 byte)

    // Log the string (0 = some logging level/type)
    Logger::log(&logEntry, 0); // FUN_00408a00

    // Clean up the temporary string
    EAString::destruct(&tempString); // FUN_00408310
}